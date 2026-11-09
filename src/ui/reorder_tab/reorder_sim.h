/**
 * @file reorder_sim.h
 * @brief Runs a program to completion on a private VM and reports cycle statistics.
 *
 * The VM is stepped by hand instead of calling ProcessorManager::run(): the pipelined run loop
 * never terminates headless, and the single-cycle `exit` ecall calls exit(0) on the whole app.
 */
#pragma once

#include "common/assembled_program.h"
#include "processor/processor_types.h"

#include <string>

namespace Kites::reorder_tab
{
struct SimResult
{
    bool finished = false;   ///< ran to the end (or to a stopping ecall)
    unsigned cycles = 0;
    unsigned retired = 0;    ///< instructions retired
    unsigned stalls = 0;
    std::string note;        ///< e.g. "stopped at exit ecall", "did not finish in N cycles"
    std::string error;       ///< runtime error from the VM, if any
};

SimResult simulateProgram(const AssembledProgram &program, ProcessorType type,
                          unsigned maxCycles = 200000);
} // namespace Kites::reorder_tab
