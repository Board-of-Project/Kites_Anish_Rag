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
namespace Kites::Reorder{


bool Check_Dependecy(
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<std::map<int,int> >&load_stores,
    std::vector<struct Instruction_Node *>&Instructions,
    struct Instruction_Node * I
);
void Initialize(std::priority_queue<struct Instruction_Node *> &Priority_List,
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<std::map<int,int> >&load_stores
);
void Update_Children(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::set<struct Instruction_Node *> &Wait_List,
    std::vector<std::map<int,int> >&load_stores,
    struct Instruction_Node *I,
    int Executed_Including_Nop,
    Kites::Reorder::Proc p
);
void Scheduler(std::vector<int>&Final_Instructions,const std::vector<uint32_t>&Hexcodes,Kites::Reorder::Proc processor,Kites::Reorder::HeuristicEntry H);
}
#endif