#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "dependency_graph.h"
#include <string>
#include <vector>
#include <map>
#include <queue>

bool Check_Dependecy(
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    struct Instruction_Node * I
);
void Initialize(std::priority_queue<struct Instruction_Node *> &Priority_List,
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations
);
void Update_Children(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<struct Instruction_Node *> &Wait_List,
    struct Instruction_Node *I,
    int Executed_Including_Nop
);
void Scheduler(std::vector<int>&Final_Instructions);

#endif