/**
 * @file main.cpp
 * @brief Entry point for the Kites command-line interface.
 */
#include "assembler/assembler.h"
#include "command_handler/command_handler.h"
#include "differential.h"
#include "reorder/reorder.h"
#include "common/assembled_program.h"
#include "common/globals.h"
#include "processor/processor_manager.h"
#include "processor/processor_types.h"
#include "repl.h"
#include "utils/utils.h"

#include <QCoreApplication>
#include <QObject>
#include <QString>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
void printUsage(const char *programName)
{
    std::cerr
        << "Usage: " << programName
        << " [assembly-file] [--vm <name>] [--mem-dump <hex_addr> <row_count>]... [--repl|-i]\n"
        << "  assembly-file   optional; if given without --repl, assembles, runs to\n"
        << "                  completion, and dumps state (batch mode)\n"
        << "  --vm <name>     rvss (default) | rv5-nh-nf | rv5-h-nf | rv5-nh-f | rv5-h-f\n"
        << "  --mem-dump      dump <row_count> 8-byte rows starting at <hex_addr>; "
           "repeatable (batch mode only)\n"
        << "  --repl, -i      drop into the interactive REPL instead of auto-running;\n"
        << "                  if assembly-file is given it is loaded before the prompt\n"
        << "  (running with no assembly-file also enters the REPL)\n"
        << "  --compare-exe <path>  differential check: run <path> <assembly-file> <generated-file>,\n"
           "                  run both files on Kites and compare results; on mismatch the\n"
           "                  input is copied to --fail-dir\n"
        << "  --fail-dir <dir>      where failing inputs are stored (default ./kites_failures)\n"
        << "  --timeout <sec>       limit for the generator and each Kites run (default 60)\n"
        << "  --reorder <n>         run the program after applying built-in reorder heuristic <n>\n"
        << "  --compare-reorder <n|all>  differential check of the built-in reorder heuristic(s):\n"
           "                  original vs reordered, in-process, no generated file\n"
        << "  --list-heuristics     print the heuristic names and their indices\n"
        << "  --compare-csr         also compare CSRs (off by default; cycle/instret differ)\n";
}

const std::unordered_map<std::string, Kites::ProcessorType> processorTypes = {
    {"rvss", Kites::ProcessorType::RVSS},
    {"rv5-nh-nf", Kites::ProcessorType::RV5Stage_NH_NF},
    {"rv5-h-nf", Kites::ProcessorType::RV5Stage_H_NF},
    {"rv5-nh-f", Kites::ProcessorType::RV5Stage_NH_F},
    {"rv5-h-f", Kites::ProcessorType::RV5Stage_H_F},
};
} // namespace

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Kites::setupVmStateDirectory();

    std::string assemblyFile;
    std::string processorTypeStr = "rvss";
    std::vector<std::string> memDumpArgs;
    bool replRequested = false;
    int reorderHeuristic = -1;
    Kites::DifferentialOptions diffOptions;
    diffOptions.failDir = "kites_failures";

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--vm")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "Error: --vm requires a value.\n";
                printUsage(argv[0]);
                return 1;
            }
            processorTypeStr = argv[++i];
        }
        else if (arg == "--mem-dump")
        {
            if (i + 2 >= argc)
            {
                std::cerr << "Error: --mem-dump requires <hex_addr> <row_count>.\n";
                printUsage(argv[0]);
                return 1;
            }
            memDumpArgs.push_back(argv[++i]);
            memDumpArgs.push_back(argv[++i]);
        }
        else if (arg == "--compare-exe" || arg == "--fail-dir" || arg == "--timeout")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "Error: " << arg << " requires a value.\n";
                printUsage(argv[0]);
                return 1;
            }
            std::string value = argv[++i];
            if (arg == "--compare-exe")
            {
                diffOptions.generatorExe = value;
            }
            else if (arg == "--fail-dir")
            {
                diffOptions.failDir = value;
            }
            else
            {
                try
                {
                    diffOptions.timeoutMs = std::stoi(value) * 1000;
                }
                catch (const std::exception &)
                {
                    std::cerr << "Error: --timeout expects a number of seconds.\n";
                    return 1;
                }
            }
        }
        else if (arg == "--list-heuristics")
        {
            const auto &names = Kites::reorder::heuristicNames();
            for (size_t n = 0; n < names.size(); ++n)
            {
                std::cout << n << ": " << names[n] << "\n";
            }
            return 0;
        }
        else if (arg == "--reorder" || arg == "--compare-reorder")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "Error: " << arg << " requires a value.\n";
                printUsage(argv[0]);
                return 1;
            }
            const std::string value = argv[++i];
            if (arg == "--compare-reorder" && value == "all")
            {
                for (size_t n = 0; n < Kites::reorder::heuristicNames().size(); ++n)
                {
                    diffOptions.reorderHeuristics.push_back(static_cast<int>(n));
                }
            }
            else
            {
                int index = -1;
                try
                {
                    index = std::stoi(value);
                }
                catch (const std::exception &)
                {
                    std::cerr << "Error: " << arg << " expects a heuristic index"
                              << (arg == "--compare-reorder" ? " or 'all'" : "") << ".\n";
                    return 1;
                }
                if (arg == "--reorder")
                {
                    reorderHeuristic = index;
                }
                else
                {
                    diffOptions.reorderHeuristics.push_back(index);
                }
            }
        }
        else if (arg == "--compare-csr")
        {
            diffOptions.compareCsrs = true;
        }
        else if (arg == "--repl" || arg == "-i")
        {
            replRequested = true;
        }
        else if (!arg.empty() && arg[0] == '-')
        {
            std::cerr << "Error: unknown argument '" << arg << "'.\n";
            printUsage(argv[0]);
            return 1;
        }
        else if (assemblyFile.empty())
        {
            assemblyFile = arg;
        }
        else
        {
            std::cerr << "Error: unexpected extra argument '" << arg << "'.\n";
            printUsage(argv[0]);
            return 1;
        }
    }

    auto processorTypeIt = processorTypes.find(processorTypeStr);
    if (processorTypeIt == processorTypes.end())
    {
        std::cerr << "Error: unknown VM type '" << processorTypeStr << "'.\n";
        printUsage(argv[0]);
        return 1;
    }

    if (!diffOptions.generatorExe.empty() || !diffOptions.reorderHeuristics.empty())
    {
        if (!diffOptions.generatorExe.empty() && !diffOptions.reorderHeuristics.empty())
        {
            std::cerr << "Error: use either --compare-exe or --compare-reorder, not both.\n";
            return 1;
        }
        if (assemblyFile.empty() || replRequested)
        {
            std::cerr << "Error: --compare-exe/--compare-reorder need an input file and cannot be combined with "
                         "--repl.\n";
            printUsage(argv[0]);
            return 1;
        }
        diffOptions.inputFile = assemblyFile;
        diffOptions.vmName = processorTypeStr;
        diffOptions.memDumpArgs = memDumpArgs;
        return Kites::RunDifferential(diffOptions);
    }

    if (replRequested || assemblyFile.empty())
    {
        Kites::ProcessorManager manager(nullptr, processorTypeIt->second);
        manager.setStepDelay(0);

        Kites::command_handler::ReplState state;
        if (!assemblyFile.empty())
        {
            try
            {
                Kites::AssembledProgram program = Kites::assemble(assemblyFile);
                manager.loadProgram(program);
                state.currentProgram = program;
                state.programLoaded = true;
                std::cout << "Loaded '" << assemblyFile << "': " << program.text_buffer.size()
                           << " instruction word(s), " << program.data_buffer.size()
                           << " data item(s).\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << "Assembly failed: " << e.what() << "\n";
            }
        }

        return Kites::RunRepl(manager, state);
    }

    Kites::AssembledProgram program;
    try
    {
        program = Kites::assemble(assemblyFile);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Assembly failed: " << e.what() << std::endl;
        return 1;
    }

    // Optional in-process reordering of the assembled machine code (text section only).
    if (reorderHeuristic >= 0)
    {
        try
        {
            const auto &names = Kites::reorder::heuristicNames();
            if (static_cast<size_t>(reorderHeuristic) >= names.size())
            {
                throw std::invalid_argument("unknown heuristic index " +
                                            std::to_string(reorderHeuristic));
            }
            std::vector<uint32_t> reordered = Kites::reorder::reorderProgram(
                program.text_buffer, processorTypeIt->second,
                static_cast<size_t>(reorderHeuristic));
            if (reordered.size() != program.text_buffer.size())
            {
                throw std::runtime_error("reordering changed the instruction count");
            }
            // Keep the reordered words for debugging / failure reports (one hex word per line).
            std::ofstream hexOut(Kites::globals::vm_state_directory / "reordered_program.hex");
            for (uint32_t word : reordered)
            {
                hexOut << std::hex << std::setw(8) << std::setfill('0') << word << "\n";
            }
            program.text_buffer = std::move(reordered);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Reorder failed: " << e.what() << std::endl;
            return 6;
        }
    }

    Kites::ProcessorManager manager(nullptr, processorTypeIt->second);

    bool runFailed = false;
    std::string runErrorMsg;
    QObject::connect(&manager, &Kites::ProcessorManager::runErrorSignal, &manager,
                      [&](const QString &message, int /*sourceLine*/)
                      {
                          runFailed = true;
                          runErrorMsg = message.toStdString();
                      });

    // ProcessorBase::step_delay_ defaults to 1000ms and is meant to pace the
    // GUI's per-instruction animation; it must be zeroed here or an N-instruction
    // program takes N seconds to run.
    manager.setStepDelay(0);
    manager.loadProgram(program);

    // Known limitation: a program hitting a blocking read syscall will hang here
    // forever, since nothing in this CLI feeds terminal stdin into the VM's input
    // queue yet (that's separate, future work).
    manager.run();

    if (runFailed)
    {
        std::cerr << "Run failed: " << runErrorMsg << std::endl;
    }

    Kites::DumpRegisters(Kites::globals::registers_dump_file_path, *manager.getRegisterFile());

    if (!memDumpArgs.empty())
    {
        try
        {
            manager.getMemoryController()->dumpMemory(memDumpArgs);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Memory dump failed: " << e.what() << std::endl;
            return 3;
        }
    }

    std::cout << "Assembled '" << assemblyFile << "': " << program.text_buffer.size()
               << " instruction word(s), " << program.data_buffer.size() << " data item(s).\n"
               << "Run " << (runFailed ? "failed" : "completed") << ".\n"
               << "Registers   -> " << Kites::globals::registers_dump_file_path.string() << "\n"
               << "Disassembly -> " << Kites::globals::disassembly_file_path.string() << "\n"
               << "Errors      -> " << Kites::globals::errors_dump_file_path.string();
    if (!memDumpArgs.empty())
    {
        std::cout << "\nMemory      -> " << Kites::globals::memory_dump_file_path.string();
    }
    std::cout << std::endl;

    return runFailed ? 2 : 0;
}
