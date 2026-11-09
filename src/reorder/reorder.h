/**
 * @file reorder.h
 * @brief Entry point for the instruction reordering algorithm.
 *
 * This header is intentionally Qt-free and UI-free so the algorithm can be unit tested and
 * also called from the CLI later. The ReorderTab only talks to this interface.
 */
#pragma once

#include "processor/processor_types.h"

#include <cstddef>
#include <cstdint>
#include <istream>
#include <string>
#include <vector>

namespace Kites::reorder
{


/**
 * @brief Reorders an assembled program.
 * @param words          machine code, one 32-bit word per instruction, exactly what
 *                       AssembledProgram::text_buffer holds (text section only).
 * @param processor      the processor model the schedule is for (hazard/forwarding rules).
 * @param heuristicIndex index into heuristicNames().
 * @return the reordered words. Must contain the same number of words as the input.
 *
 * Remember: branch/jump immediates are PC-relative, so if you move instructions across a
 * branch target or move a branch itself, the offsets must be re-encoded here.
 */
std::vector<uint32_t> reorderProgram(const std::vector<uint32_t> &words, ProcessorType processor,
                                     std::size_t heuristicIndex);
const std::vector<std::string> &heuristicNames();

} // namespace Kites::reorder