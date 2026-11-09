#include "reorder_listing.h"

#include "assembler/assembler.h"
#include "common/globals.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

namespace Kites::reorder_tab
{
namespace
{
constexpr uint32_t kOpBranch = 0x63;
constexpr uint32_t kOpJal = 0x6F;

/// Branch/jump words differ only in the immediate after re-encoding, so compare with the
/// immediate bits cleared.
uint32_t keyOf(uint32_t w)
{
    switch (w & 0x7F)
    {
    case kOpBranch:
        return w & 0x01FFF07F;
    case kOpJal:
        return w & 0x00000FFF;
    default:
        return w;
    }
}

int32_t signExtend(uint32_t value, int bits)
{
    const uint32_t m = 1u << (bits - 1);
    return static_cast<int32_t>((value ^ m) - m);
}

int32_t branchImmediate(uint32_t w)
{
    const uint32_t imm = ((w >> 31) & 1) << 12 | ((w >> 7) & 1) << 11 | ((w >> 25) & 0x3F) << 5 |
                         ((w >> 8) & 0xF) << 1;
    return signExtend(imm, 13);
}

int32_t jalImmediate(uint32_t w)
{
    const uint32_t imm = ((w >> 31) & 1) << 20 | ((w >> 12) & 0xFF) << 12 |
                         ((w >> 20) & 1) << 11 | ((w >> 21) & 0x3FF) << 1;
    return signExtend(imm, 21);
}

std::vector<std::string> splitOperands(const std::string &s)
{
    std::vector<std::string> parts;
    std::string current;
    for (char c : s)
    {
        if (c == ',')
        {
            parts.push_back(current);
            current.clear();
        }
        else if (c != ' ')
        {
            current += c;
        }
    }
    if (!current.empty())
    {
        parts.push_back(current);
    }
    return parts;
}

/// The assembler's internal text ("lw x9, x2, 0 <label>") -> source form ("lw x9, 0(x2)").
std::string toSourceForm(std::string text)
{
    // drop the trailing "<label>" annotation
    const size_t angle = text.rfind(" <");
    if (angle != std::string::npos && !text.empty() && text.back() == '>')
    {
        text.erase(angle);
    }

    static const std::unordered_set<std::string> loads = {"lb",  "lh",  "lw",  "ld", "lbu",
                                                          "lhu", "lwu", "flw", "fld"};
    static const std::unordered_set<std::string> stores = {"sb", "sh", "sw", "sd", "fsw", "fsd"};

    const size_t space = text.find(' ');
    if (space == std::string::npos)
    {
        return text;
    }
    const std::string op = text.substr(0, space);
    const std::vector<std::string> a = splitOperands(text.substr(space + 1));
    if (a.size() == 3 && (loads.count(op) || op == "jalr"))
    {
        return op + " " + a[0] + ", " + a[2] + "(" + a[1] + ")"; // rd, imm(rs1)
    }
    if (a.size() == 3 && stores.count(op))
    {
        return op + " " + a[1] + ", " + a[2] + "(" + a[0] + ")"; // src, imm(base)
    }
    return text;
}

std::string withOffset(const std::string &text, int32_t offset)
{
    const size_t comma = text.rfind(", ");
    if (comma == std::string::npos)
    {
        return text;
    }
    return text.substr(0, comma + 2) + std::to_string(offset);
}
} // namespace

Listing buildListing(const AssembledProgram &original, const std::vector<uint32_t> &words)
{
    std::unordered_map<uint32_t, std::string> templates;
    const size_t known = std::min(original.text_buffer.size(), original.intermediate_code.size());
    for (size_t i = 0; i < known; ++i)
    {
        std::ostringstream os;
        os << original.intermediate_code[i].first;
        templates.emplace(keyOf(original.text_buffer[i]), toSourceForm(os.str()));
    }

    Listing listing;
    listing.complete = true;
    for (uint32_t w : words)
    {
        auto it = templates.find(keyOf(w));
        if (it == templates.end())
        {
            listing.lines.emplace_back();
            listing.complete = false;
            continue;
        }
        std::string text = it->second;
        if ((w & 0x7F) == kOpBranch)
        {
            text = withOffset(text, branchImmediate(w));
        }
        else if ((w & 0x7F) == kOpJal)
        {
            text = withOffset(text, jalImmediate(w));
        }
        listing.lines.push_back(std::move(text));
    }
    return listing;
}

std::string joinLines(const std::vector<std::string> &lines)
{
    std::string out;
    for (const std::string &line : lines)
    {
        out += line + "\n";
    }
    return out;
}

std::string joinHex(const std::vector<uint32_t> &words)
{
    std::ostringstream os;
    for (uint32_t w : words)
    {
        os << std::hex << std::setw(8) << std::setfill('0') << w << "\n";
    }
    return os.str();
}

bool verifyAssembly(const std::vector<std::string> &lines, const std::vector<uint32_t> &expected,
                    std::string &why)
{
    for (const std::string &line : lines)
    {
        if (line.empty())
        {
            why = "some instructions have no text";
            return false;
        }
    }
    try
    {
        const std::filesystem::path scratch = globals::vm_state_directory / "reorder_verify.s";
        {
            std::ofstream out(scratch);
            out << joinLines(lines);
        }
        const AssembledProgram program = assemble(scratch.string());
        if (program.text_buffer != expected)
        {
            why = "re-assembled code differs from the reordered words";
            return false;
        }
        return true;
    }
    catch (const std::exception &e)
    {
        why = std::string("re-assembly failed: ") + e.what();
        return false;
    }
}
} // namespace Kites::reorder_tab
