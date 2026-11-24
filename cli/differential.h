/**
 * @file differential.h
 * @brief Differential check for kites-cli: run a program on Kites, run an external C++
 *        executable on the same file to produce a second program, run that on Kites too, and
 *        verify that both runs end in the same architectural state.
 */
#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace Kites
{
    struct DifferentialOptions
    {
        std::string inputFile;             ///< program given on the command line
        std::string generatorExe;          ///< executable invoked as: <exe> <inputFile> <outputFile>
        /// Alternative to generatorExe: apply these built-in reorder heuristic combinations
        /// in-process (no files involved). Each entry is one run, and is itself a list of heuristic
        /// indices that together form the priority vector (e.g. {0,2} = heuristics 0 then 2).
        std::vector<std::vector<int>> reorderHeuristics;
        std::filesystem::path failDir;     ///< where failing inputs are copied
        std::string vmName = "rvss";       ///< forwarded to kites-cli --vm
        std::vector<std::string> memDumpArgs; ///< <hex_addr> <rows> pairs, compared when non-empty
        int timeoutMs = 60000;             ///< limit for the generator and for each Kites run
        std::string cyclesOriginalFile;    ///< append the original program's total cycles here
        std::string cyclesModifiedFile;    ///< append the reordered/generated program's cycles here
        unsigned maxCycles = 0;            ///< forwarded to each Kites run when non-zero
        bool compareCsrs = false; ///< cycle/instret style CSRs legitimately differ, so off by default
    };

    /// Process exit codes used by the differential mode (0-3 are shared with the normal CLI).
    enum DifferentialExit
    {
        DiffMatch = 0,
        DiffBadInput = 1,      ///< the original input did not assemble / run setup failed
        DiffMismatch = 4,       ///< the two runs disagree (input stored in failDir)
        DiffGeneratorFail = 5, ///< the executable crashed, timed out or produced no file (stored)
    };

    /**
     * @brief Runs the full check described in the file comment.
     * @return one of DifferentialExit.
     */
    int runDifferential(const DifferentialOptions &options);
} // namespace Kites
