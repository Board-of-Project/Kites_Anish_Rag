/**
 * @file differential.cpp
 * @brief Implementation of the kites-cli differential check.
 *
 * Every Kites run is done in a *child* kites-cli process rather than in-process, because the
 * VM's `exit` ecall calls exit(0) and would terminate the checker itself after the first run.
 * Child processes also give us crash isolation and a timeout for runaway programs.
 */
#include "differential.h"

#include "common/globals.h"
#include "reorder/reorder.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTemporaryDir>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

namespace Kites
{
    namespace
    {
        namespace fs = std::filesystem;

        /// Everything we compare between the two runs.
        struct Snapshot
        {
            bool launched = false;         ///< child started and finished within the timeout
            std::string launchError;       ///< why it did not (crash / timeout / cannot start)
            int exitCode = 0;              ///< kites-cli exit code: 0 ok, 1 assembly failed, 2 run error
            std::string programOutput;     ///< syscall output only (step/PC noise filtered out)
            std::map<std::string, std::string> gpr, fpr, csr; ///< register name -> hex string
            std::string memoryDump;
            std::string registersError;    ///< set if registers_dump.json could not be parsed
            long long cycles = -1;         ///< total cycles, -1 if the child did not report any
            std::string reorderError;      ///< "Reorder failed: ..." text from a child that exit(6)'d
        };

        std::string readFile(const fs::path &path)
        {
            std::ifstream in(path);
            std::ostringstream ss;
            ss << in.rdbuf();
            return ss.str();
        }

        /// Keeps only the program's own output: "[Syscall output: ...]" blocks and the exit line.
        /// Everything else the VM prints (PC trace, VM_* status words, summary lines with file names
        /// and instruction counts) legitimately differs between two equivalent programs.
        std::string extractProgramOutput(const std::string &raw)
        {
            std::istringstream in(raw);
            std::string line, out;
            bool inBlock = false;
            while (std::getline(in, line))
            {
                if (!inBlock && line.rfind("[Syscall output: ", 0) == 0)
                {
                    inBlock = true;
                }
                if (inBlock || line.rfind("Exited with exit code:", 0) == 0)
                {
                    out += line + "\n";
                    if (inBlock && !line.empty() && line.back() == ']')
                    {
                        inBlock = false; // a string containing newlines spans several lines
                    }
                }
            }
            return out;
        }

        std::map<std::string, std::string> jsonSection(const QJsonObject &root, const char *key)
        {
            std::map<std::string, std::string> result;
            const QJsonObject section = root.value(key).toObject();
            for (auto it = section.begin(); it != section.end(); ++it)
            {
                result[it.key().toStdString()] = it.value().toString().toStdString();
            }
            return result;
        }

        /// kites-cli exit code meaning "the reorder step itself threw" (see cli/main.cpp).
        constexpr int kReorderFailedExit = 6;

        fs::path cyclesPath()
        {
            return globals::vm_state_directory / "cycles_out.txt";
        }

        fs::path reorderedHexPath()
        {
            return globals::vm_state_directory / "reordered_program.hex";
        }

        /// "0,2,3" for {0,2,3}: the form accepted by kites-cli --reorder.
        std::string joinHeuristics(const std::vector<int> &hs, const char *sep = ",")
        {
            std::string out;
            for (size_t i = 0; i < hs.size(); ++i)
            {
                out += (i ? sep : "") + std::to_string(hs[i]);
            }
            return out;
        }

        /// A non-empty reorderHeuristics makes the child apply those built-in heuristics (as one priority
        /// vector) before running.
        Snapshot runKites(const std::string &file, const DifferentialOptions &opt,
                          const std::vector<int> &reorderHeuristics = {})
        {
            Snapshot snap;

            // Truncate previous dumps so a stale file can never be mistaken for this run's result.
            std::ofstream(globals::registers_dump_file_path, std::ios::trunc).close();
            std::ofstream(globals::memory_dump_file_path, std::ios::trunc).close();
            std::error_code removeEc;
            fs::remove(reorderedHexPath(), removeEc);
            fs::remove(cyclesPath(), removeEc);

            QStringList args{QString::fromStdString(file), "--vm", QString::fromStdString(opt.vmName)};
            // memDumpArgs is a flat <addr> <rows> list; each pair needs its own --mem-dump flag.
            if (!opt.cyclesOriginalFile.empty() || !opt.cyclesModifiedFile.empty())
            {
                args << "--cycles-out" << QString::fromStdString(cyclesPath().string());
            }
            if (opt.maxCycles != 0)
            {
                args << "--max-cycles" << QString::number(opt.maxCycles);
            }
            if (!reorderHeuristics.empty())
            {
                args << "--reorder" << QString::fromStdString(joinHeuristics(reorderHeuristics));
            }
            for (size_t i = 0; i + 1 < opt.memDumpArgs.size(); i += 2)
            {
                args << "--mem-dump" << QString::fromStdString(opt.memDumpArgs[i])
                << QString::fromStdString(opt.memDumpArgs[i + 1]);
            }

            QProcess proc;
            proc.setProgram(QCoreApplication::applicationFilePath());
            proc.setArguments(args);
            proc.setProcessChannelMode(QProcess::SeparateChannels);
            proc.start();
            if (!proc.waitForStarted(5000))
            {
                snap.launchError = "could not start kites-cli: " + proc.errorString().toStdString();
                return snap;
            }
            if (!proc.waitForFinished(opt.timeoutMs))
            {
                proc.kill();
                proc.waitForFinished(2000);
                snap.launchError = "kites run timed out after " + std::to_string(opt.timeoutMs) + " ms";
                return snap;
            }
            if (proc.exitStatus() != QProcess::NormalExit)
            {
                snap.launchError = "kites run crashed";
                return snap;
            }

            snap.launched = true;
            snap.exitCode = proc.exitCode();
            if (snap.exitCode == kReorderFailedExit)
            {
                std::istringstream err(proc.readAllStandardError().toStdString());
                std::string line;
                while (std::getline(err, line))
                {
                    if (line.rfind("Reorder failed:", 0) == 0)
                    {
                        snap.reorderError += line + "\n";
                    }
                }
                return snap; // nothing meaningful was run
            }
            snap.programOutput = extractProgramOutput(proc.readAllStandardOutput().toStdString());

            QFile regFile(QString::fromStdString(globals::registers_dump_file_path.string()));
            if (regFile.open(QIODevice::ReadOnly))
            {
                QJsonParseError parseError;
                const QJsonDocument doc = QJsonDocument::fromJson(regFile.readAll(), &parseError);
                if (doc.isObject())
                {
                    snap.gpr = jsonSection(doc.object(), "gp_registers");
                    snap.fpr = jsonSection(doc.object(), "fp_registers");
                    snap.csr = jsonSection(doc.object(), "control and status registers");
                }
                else
                {
                    snap.registersError = parseError.errorString().toStdString();
                }
            }
            else if (snap.exitCode != 1) // exit code 1 = assembly failed, no registers expected
            {
                snap.registersError = "registers_dump.json missing";
            }

            snap.memoryDump = readFile(globals::memory_dump_file_path);

            std::ifstream cyclesIn(cyclesPath());
            long long cycles = -1;
            if (cyclesIn >> cycles)
            {
                snap.cycles = cycles;
            }
            return snap;
        }

        void compareMaps(const std::string &label, const std::map<std::string, std::string> &a,
                         const std::map<std::string, std::string> &b, std::vector<std::string> &diffs)
        {
            for (const auto &[name, value] : a)
            {
                auto it = b.find(name);
                const std::string other = it == b.end() ? "<missing>" : it->second;
                if (value != other)
                {
                    diffs.push_back(label + name + ": original " + value + ", generated " + other);
                }
            }
        }

        std::vector<std::string> splitLines(const std::string &text)
        {
            std::vector<std::string> lines;
            std::istringstream in(text);
            std::string line;
            while (std::getline(in, line))
            {
                lines.push_back(line);
            }
            return lines;
        }

        /// Returns human-readable differences; empty means the two runs match.
        std::vector<std::string> compare(const Snapshot &a, const Snapshot &b, bool compareCsrs)
        {
            std::vector<std::string> diffs;

            if (!b.launched)
            {
                diffs.push_back("generated program: " + b.launchError);
                return diffs;
            }
            if (a.exitCode != b.exitCode)
            {
                diffs.push_back("kites exit code differs: original " + std::to_string(a.exitCode) +
                ", generated " + std::to_string(b.exitCode) +
                " (1 = assembly failed, 2 = runtime error, 7 = did not finish)");
            }
            if (!b.registersError.empty() || !a.registersError.empty())
            {
                diffs.push_back("register dump problem: original '" + a.registersError +
                "', generated '" + b.registersError + "'");
            }
            if (a.programOutput != b.programOutput)
            {
                diffs.push_back("program output differs:\n    original : " + a.programOutput +
                "\n    generated: " + b.programOutput);
            }

            compareMaps("", a.gpr, b.gpr, diffs);
            compareMaps("", a.fpr, b.fpr, diffs);
            if (compareCsrs)
            {
                compareMaps("csr ", a.csr, b.csr, diffs);
            }

            if (a.memoryDump != b.memoryDump)
            {
                const std::vector<std::string> la = splitLines(a.memoryDump);
                const std::vector<std::string> lb = splitLines(b.memoryDump);
                for (size_t i = 0; i < std::max(la.size(), lb.size()); ++i)
                {
                    const std::string sa = i < la.size() ? la[i] : "<missing>";
                    const std::string sb = i < lb.size() ? lb[i] : "<missing>";
                    if (sa != sb)
                    {
                        diffs.push_back("memory line " + std::to_string(i + 1) + ": original " + sa +
                        ", generated " + sb);
                    }
                }
            }
            return diffs;
        }

        /// Copies the failing input into failDir; report and generated file go to failDir/details.
        fs::path storeFailure(const DifferentialOptions &opt, const fs::path &generatedFile,
                              const std::string &report, const std::string &tag = "",
                              const std::string &generatedSuffix = "")
        {
            const fs::path input(opt.inputFile);
            const std::string stamp =
            QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss_zzz").toStdString();
            const std::string base =
            input.stem().string() + (tag.empty() ? "" : "_" + tag) + "_" + stamp;

            std::error_code ec;
            fs::create_directories(opt.failDir / "details", ec);
            if (ec)
            {
                throw std::runtime_error("Unable to create fail directory '" + opt.failDir.string() +
                "': " + ec.message());
            }

            const fs::path storedInput = opt.failDir / (base + input.extension().string());
            fs::copy_file(input, storedInput, fs::copy_options::overwrite_existing);

            std::ofstream(opt.failDir / "details" / (base + ".report.txt")) << report;
            if (!generatedFile.empty() && fs::exists(generatedFile))
            {
                const std::string suffix =
                generatedSuffix.empty() ? ".generated" + input.extension().string() : generatedSuffix;
                fs::copy_file(generatedFile, opt.failDir / "details" / (base + suffix),
                              fs::copy_options::overwrite_existing);
            }
            return storedInput;
        }

        void storeAndAnnounce(const DifferentialOptions &opt, const fs::path &generatedFile,
                              const std::string &report, const std::string &tag = "",
                              const std::string &generatedSuffix = "")
        {
            try
            {
                std::cerr << "Stored copy: "
                << storeFailure(opt, generatedFile, report, tag, generatedSuffix).string()
                << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << "Could not store failing input: " << e.what() << std::endl;
            }
        }


        /// Appends one line to each requested cycles file. Only done when both runs reported cycles, so
        /// line N of the two files always belongs to the same comparison.
        void appendCycles(const DifferentialOptions &opt, const Snapshot &original,
                          const Snapshot &modified)
        {
            if (original.cycles < 0 || modified.cycles < 0)
            {
                return;
            }
            if (!opt.cyclesOriginalFile.empty())
            {
                std::ofstream(opt.cyclesOriginalFile, std::ios::app) << original.cycles << "\n";
            }
            if (!opt.cyclesModifiedFile.empty())
            {
                std::ofstream(opt.cyclesModifiedFile, std::ios::app) << modified.cycles << "\n";
            }

        }

        std::string cyclesSuffix(const Snapshot &original, const Snapshot &modified)
        {
            if (original.cycles < 0 || modified.cycles < 0)
            {
                return "";
            }
            return " [cycles " + std::to_string(original.cycles) + " -> " +
            std::to_string(modified.cycles) + "]";
        }

        /// In-process reordering: for each heuristic, a child kites-cli applies reorderProgram() to the
        /// assembled words and runs the result directly. No generated file is written or parsed.
        int runReorderChecks(const DifferentialOptions &opt, const Snapshot &original)
        {
            const auto &names = reorder::heuristicNames();
            int worst = DiffMatch;

            for (const std::vector<int> &hs : opt.reorderHeuristics)
            {
                if (hs.empty())
                {
                    std::cerr << "Empty heuristic list" << std::endl;
                    return DiffBadInput;
                }
                std::string nameList;
                for (int h : hs)
                {
                    if (h < 0 || static_cast<size_t>(h) >= names.size())
                    {
                        std::cerr << "Unknown heuristic index " << h << " (valid: 0.." << names.size() - 1
                        << ")" << std::endl;
                        return DiffBadInput;
                    }
                    nameList += (nameList.empty() ? "" : " + ") + names[h];
                }
                const std::string label = std::string(hs.size() > 1 ? "heuristics " : "heuristic ") +
                joinHeuristics(hs) + " (" + nameList + ")";
                const std::string tag = "h" + joinHeuristics(hs, "-");

                const Snapshot reordered = runKites(opt.inputFile, opt, hs);

                // The reorder step itself failed: crashed, timed out, or threw.
                if (!reordered.launched || reordered.exitCode == kReorderFailedExit)
                {
                    const std::string why = !reordered.launched ? reordered.launchError
                    : reordered.reorderError;
                    std::ostringstream report;
                    report << "Input: " << opt.inputFile << "\nReorder " << label << " failed: " << why
                    << "\n";
                    std::cerr << "FAIL " << label << ": " << why << std::endl;
                    storeAndAnnounce(opt, {}, report.str(), tag);
                    worst = DiffGeneratorFail;
                    continue;
                }

                const std::vector<std::string> diffs = compare(original, reordered, opt.compareCsrs);
                appendCycles(opt, original, reordered);
                if (diffs.empty())
                {
                    std::cout << "MATCH " << label << cyclesSuffix(original, reordered) << std::endl;
                    continue;
                }

                std::ostringstream report;
                report << "Input: " << opt.inputFile << "\nReorder " << label
                << cyclesSuffix(original, reordered) << "\n"
                << diffs.size() << " difference(s):\n";
                for (const std::string &d : diffs)
                {
                    report << "  - " << d << "\n";
                }
                std::cerr << "MISMATCH " << label << ": " << report.str();
                storeAndAnnounce(opt, reorderedHexPath(), report.str(), tag, ".reordered.hex");
                if (worst != DiffGeneratorFail)
                {
                    worst = DiffMismatch;
                }
            }
            return worst;
        }
    } // namespace

    int runDifferential(const DifferentialOptions &opt)
    {
        // 1. Run the original input on Kites.
        const Snapshot original = runKites(opt.inputFile, opt);
        if (!original.launched || original.exitCode == 1 || original.exitCode == 7)
        {
            std::cerr << "Original input could not be run on Kites ("
            << (!original.launched ? original.launchError
            : original.exitCode == 7 ? "it did not finish (infinite loop?)"
            : "assembly failed")
            << "); nothing to compare." << std::endl;
            return DiffBadInput;
        }

        // 2a. Built-in reordering (no external executable, no generated file).
        if (!opt.reorderHeuristics.empty())
        {
            return runReorderChecks(opt, original);
        }

        // 2b. Run the external executable: <exe> <input> <output>.
        QTemporaryDir tmp;
        if (!tmp.isValid())
        {
            std::cerr << "Unable to create a temporary directory." << std::endl;
            return DiffGeneratorFail;
        }
        const fs::path generatedFile = fs::path(tmp.path().toStdString()) /
        ("generated" + fs::path(opt.inputFile).extension().string());

        QProcess gen;
        gen.setProgram(QString::fromStdString(opt.generatorExe));
        gen.setArguments(
            {QString::fromStdString(opt.inputFile), QString::fromStdString(generatedFile.string())});
        gen.start();

        std::string problem;
        if (!gen.waitForStarted(5000))
        {
            problem = "could not start '" + opt.generatorExe + "': " + gen.errorString().toStdString();
        }
        else if (!gen.waitForFinished(opt.timeoutMs))
        {
            gen.kill();
            gen.waitForFinished(2000);
            problem = "timed out after " + std::to_string(opt.timeoutMs) + " ms";
        }
        else if (gen.exitStatus() != QProcess::NormalExit)
        {
            problem = "crashed";
        }
        else if (gen.exitCode() != 0)
        {
            problem = "exited with code " + std::to_string(gen.exitCode());
        }
        else if (!fs::exists(generatedFile))
        {
            problem = "did not create the output file";
        }

        if (!problem.empty())
        {
            std::ostringstream report;
            report << "Input: " << opt.inputFile << "\nGenerator '" << opt.generatorExe << "' "
            << problem << "\nstderr:\n"
            << gen.readAllStandardError().toStdString() << "\n";
            std::cerr << "FAIL: generator " << problem << std::endl;
            storeAndAnnounce(opt, {}, report.str());
            return DiffGeneratorFail;
        }

        // 3. Run the generated file on Kites and compare.
        const Snapshot generated = runKites(generatedFile.string(), opt);
        const std::vector<std::string> diffs = compare(original, generated, opt.compareCsrs);
        appendCycles(opt, original, generated);

        if (diffs.empty())
        {
            std::cout << "MATCH: '" << opt.inputFile
            << "' and its generated file produce identical results."
            << cyclesSuffix(original, generated) << std::endl;
            return DiffMatch;
        }

        std::ostringstream report;
        report << "Input: " << opt.inputFile << "\nGenerator: " << opt.generatorExe << "\n"
        << diffs.size() << " difference(s):\n";
        for (const std::string &d : diffs)
        {
            report << "  - " << d << "\n";
        }
        std::cerr << "MISMATCH: " << report.str();
        storeAndAnnounce(opt, generatedFile, report.str());
        return DiffMismatch;
    }
} // namespace Kites
