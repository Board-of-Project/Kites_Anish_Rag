/**
 * @file reorder_sim.h
 * @brief Runs a program to completion on a private processor and reports cycle statistics.
 *
 * The processor is driven directly through ProcessorBase::StepAndNotify(), which returns
 * whether any work is left. ProcessorManager::step() is deliberately not used: when the program
 * finishes it calls RequestStop(), which resets the whole VM and wipes the counters. Nor is
 * run(): LoadProgram() adds a breakpoint at the end of the program that pauses the pipelined
 * VMs while they drain, and nothing resumes them here.
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
    std::string note;        ///< e.g. "stopped at input ecall", "did not finish in N cycles"
    std::string error;       ///< runtime error from the VM, if any
};

SimResult simulateProgram(const AssembledProgram &program, ProcessorType type,
                          unsigned maxCycles = 200000);
} // namespace Kites::reorder_tab
