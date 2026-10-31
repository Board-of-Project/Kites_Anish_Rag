#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "dependency_graph.h"
#include <vector>
#include <map>

void Heuristic1(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations
);
void Heuristic2(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations
);
#endif