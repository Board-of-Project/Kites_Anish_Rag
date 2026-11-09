#include "reordering.h"
#include "scheduler.h"
#include "dependency_graph.h"
#include "translator.h"
#include "utils.h"
#include "processor/processor_types.h"
#include "heuristic.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
// Every heuristic has this same signature:
namespace Kites::Reorder{
using HeuristicFn =void (*)(
    std::vector<struct Kites::Reorder::Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Kites::Reorder::Proc p
);

// Index in this table == the `heuristic` value == the dropdown position.
const HeuristicEntry kHeuristics[] = {
    {"Weighted subtree", &(Kites::Reorder::Heuristic1)},
    {"Index", &(Kites::Reorder::Heuristic2)},
};
constexpr size_t kHeuristicCount = sizeof(kHeuristics) / sizeof(kHeuristics[0]);

size_t heuristicCount()
{
    return kHeuristicCount;
}

const char * heuristicName(size_t index)
{
    return index < kHeuristicCount ? kHeuristics[index].name : "";
}

// call the main function
std::vector<uint32_t> reorderer(const std::vector<uint32_t>&Hexcodes,Proc processor,size_t Heuristic) {
    std::vector<int> finalorder;
    Scheduler(finalorder, Hexcodes,processor,Kites::Reorder::kHeuristics[Heuristic]);
    std::vector<uint32_t> Final;
    for(int i:finalorder){
        if(i>=0){
            Final.push_back(Hexcodes[i]);
        }
    }
    return Final;
}
}
