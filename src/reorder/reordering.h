#ifndef REORDERING_H
#define REORDERING_H
#include <cstdint>
#include <vector>
#include "utils.h"
namespace Kites::reorder
{
// takes the assembled hex words, returns the same words in the new order
// `heuristics` = indices into the heuristic table; each one appends a component to every
// instruction's priority vector, in the order given.
// If `originalIndex` is given it receives, for every output word, the index it had in `words`
// (originalIndex[k] = original position of reordered instruction k).
std::vector<uint32_t> reorderer(const std::vector<uint32_t> &words, Proc proc,
                                const std::vector<size_t> &heuristics,
                                std::vector<size_t> *originalIndex = nullptr);
size_t heuristicCount();
const char *heuristicName(size_t index);

}
#endif