/**
 * @file reorder_listing.h
 * @brief Turns reordered machine words back into assembly text that can be copied and pasted
 *        into the editor, and verifies the text by assembling it again.
 */
#pragma once

#include "common/assembled_program.h"

#include <cstdint>
#include <string>
#include <vector>

namespace Kites::reorder_tab
{
struct Listing
{
    /// One assembly line per word. Empty when no text could be derived for that word.
    std::vector<std::string> lines;
    bool complete = false; ///< every word has text
};

/**
 * @brief Builds assembly text for @p words using the instruction text of @p original.
 *
 * Words that exist unchanged in the original reuse its text. Branch/jump words whose offset was
 * re-encoded (same registers, new immediate) get the text with the new numeric offset.
 */
Listing buildListing(const AssembledProgram &original, const std::vector<uint32_t> &words);

/// Newline-joined lines (for the clipboard).
std::string joinLines(const std::vector<std::string> &lines);

/// One 8-digit hex word per line.
std::string joinHex(const std::vector<uint32_t> &words);

/**
 * @brief Assembles @p lines and checks they encode exactly @p expected.
 * @param why filled with a reason when this returns false.
 */
bool verifyAssembly(const std::vector<std::string> &lines, const std::vector<uint32_t> &expected,
                    std::string &why);
} // namespace Kites::reorder_tab
