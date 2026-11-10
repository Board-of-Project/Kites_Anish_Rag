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
    std::vector<int> reorderHeuristics; ///< alternative to generatorExe: apply these built-in
                                        ///< reorder heuristics in-process (no files involved)
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
    DIFF_MATCH = 0,
    DIFF_BAD_INPUT = 1,      ///< the original input did not assemble / run setup failed
    DIFF_MISMATCH = 4,       ///< the two runs disagree (input stored in failDir)
    DIFF_GENERATOR_FAIL = 5, ///< the executable crashed, timed out or produced no file (stored)
};

/**
 * @brief Runs the full check described in the file comment.
 * @return one of DifferentialExit.
 */
int RunDifferential(const DifferentialOptions &options);
} // namespace Kites
