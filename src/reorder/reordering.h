#ifndef REORDERING_H
#define REORDERING_H
#include <cstdint>
#include <vector>
#include "utils.h"
namespace Kites::Reorder
{
// takes the assembled hex words, returns the same words in the new order
std::vector<uint32_t> reorderer(const std::vector<uint32_t> &words, Proc proc, size_t heuristic);
size_t heuristicCount();
const char *heuristicName(size_t index);

}
#endif