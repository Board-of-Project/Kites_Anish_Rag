#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "dependency_graph.h"
#include "utils.h"
#include <vector>
#include <map>

namespace Kites::Reorder{

using HeuristicFn =void (*)(
    std::vector<struct Kites::Reorder::Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Proc p
);

struct HeuristicEntry
{
    const char *name;  // shown in the dropdown
    HeuristicFn fn;
};
void Heuristic1(
    std::vector<struct Kites::Reorder::Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Proc p
);
void Heuristic2(
    std::vector<struct Kites::Reorder::Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Proc p
);
}
#endif