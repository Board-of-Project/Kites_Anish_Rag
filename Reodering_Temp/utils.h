#ifndef UTILS_H
#define UTILS_H

#include "dependency_graph.h"
bool overlap(int h1,int h2,int l1,int l2);

int Nops_Needed(struct Instruction_Node * &I1,struct Instruction_Node * &I2);

void Num_Hazards(std::vector <std::vector <struct Instruction_Node*>>& Instruction_blocks);
#endif