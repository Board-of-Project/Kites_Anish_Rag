#ifndef UTILS_H
#define UTILS_H

#include "dependency_graph.h"
bool overlap(int h1,int h2,int l1,int l2);

namespace Kites::reorder{
enum class Proc { SingleCycle, NoHazardNoFwd, HazardNoFwd, NoHazardFwd, HazardFwd };
int nopsNeeded(struct Kites::reorder::InstructionNode * &node1,struct Kites::reorder::InstructionNode * &node2,Kites::reorder::Proc processor);

void numHazards(std::vector <std::vector <struct Kites::reorder::InstructionNode*>>& instructionBlocks,Kites::reorder::Proc processor);
int edge(struct InstructionNode *node1,struct InstructionNode *node2);
}



#endif