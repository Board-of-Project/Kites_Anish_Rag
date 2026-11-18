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
        {"RL model dummy",&(Kites::Reorder::HeuristicRL1)},
        {"RL model dummy",&(Kites::Reorder::HeuristicRL2)},
        {"RL model",&(Kites::Reorder::HeuristicRL)},
        {"No Heuristic(all 0 priority)",&(Kites::Reorder::HeuristicNull)}
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
    std::vector<uint32_t> reorderer(const std::vector<uint32_t>&Hexcodes,Proc processor,const std::vector<size_t>&Heuristics) {
        if(Heuristics.empty()){
            throw std::invalid_argument("at least one heuristic is required");
        }
        std::vector<HeuristicEntry> chosen;
        for(size_t h : Heuristics){
            if(h >= kHeuristicCount){
                throw std::invalid_argument("unknown heuristic index " + std::to_string(h));
            }
            chosen.push_back(kHeuristics[h]);
        }
        std::vector<int> finalorder;
        Scheduler(finalorder, Hexcodes,processor,chosen);
        std::vector<uint32_t> Final;
        for(int i:finalorder){
            if(i>=0){
                Final.push_back(Hexcodes[i]);
            }
        }
        return Final;
    }
}
