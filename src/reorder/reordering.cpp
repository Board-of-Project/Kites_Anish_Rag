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
#include <string>
// Every heuristic has this same signature:
namespace Kites::reorder{
using HeuristicFn =void (*)(
    std::vector<struct Kites::reorder::InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Kites::reorder::Proc p
);

// Index in this table == the `heuristic` value == the dropdown position.
const HeuristicEntry kHeuristics[] = {
    {"Entire subtree", &(Kites::reorder::heuristic1)},
    {"Index", &(Kites::reorder::heuristic2)},
    {"RL model",&(Kites::reorder::heuristicRl)},
    {"No Heuristic(all 0 priority)",&(Kites::reorder::heuristicNull)},
    {"children",&(Kites::reorder::heuristicChildren)},
    {"Deepest subtree",&(Kites::reorder::heuristicDeep)}
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
std::vector<uint32_t> reorderer(const std::vector<uint32_t>&hexcodes,Proc processor,const std::vector<size_t>&heuristics,std::vector<size_t>*originalIndex) {
    if(heuristics.empty()){
        throw std::invalid_argument("at least one heuristic is required");
    }
    std::vector<HeuristicEntry> chosen;
    for(size_t h : heuristics){
        if(h >= kHeuristicCount){
            throw std::invalid_argument("unknown heuristic index " + std::to_string(h));
        }
        chosen.push_back(kHeuristics[h]);
    }
    std::vector<int> finalOrder;
    scheduler(finalOrder, hexcodes,processor,chosen);
    std::vector<uint32_t> finalWords;
    if(originalIndex){
        originalIndex->clear();
    }
    for(int i:finalOrder){
        if(i>=0){
            finalWords.push_back(hexcodes[i]);
            if(originalIndex){
                originalIndex->push_back(static_cast<size_t>(i));
            }
        }
    }
    return finalWords;
}
}
