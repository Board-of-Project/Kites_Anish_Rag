#ifndef UTILS_H
#define UTILS_H

#include "dependency_graph.h"
bool overlap(int h1,int h2,int l1,int l2);

namespace Kites::Reorder{
enum class Proc { SingleCycle, NoHazardNoFwd, HazardNoFwd, NoHazardFwd, HazardFwd };
int Nops_Needed(struct Kites::Reorder::Instruction_Node * &I1,struct Kites::Reorder::Instruction_Node * &I2,Kites::Reorder::Proc processor);

void Num_Hazards(std::vector <std::vector <struct Kites::Reorder::Instruction_Node*>>& Instruction_blocks,Kites::Reorder::Proc processor);
}

#endif