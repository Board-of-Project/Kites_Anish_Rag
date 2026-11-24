#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "dependency_graph.h"
#include "utils.h"
#include "heuristic.h"
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>

bool overlap(int h1,int h2,int l1,int l2);
namespace Kites::reorder{


bool checkDependecy(
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<std::map<int,int> >&loadStores,
    std::vector<struct InstructionNode *>&instructions,
    struct InstructionNode * node
);
void initialize(std::priority_queue<struct InstructionNode *> &priorityList,
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<std::map<int,int> >&loadStores
);
void updateChildren(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::set<struct InstructionNode *> &waitList,
    std::vector<std::map<int,int> >&loadStores,
    struct InstructionNode *node,
    int executedIncludingNop,
    Kites::reorder::Proc p
);
void scheduler(std::vector<int>&finalInstructions,const std::vector<uint32_t>&hexcodes,Kites::reorder::Proc processor,std::vector<Kites::reorder::HeuristicEntry> heuristics);
}
#endif