#include "dependency_graph.h"
#include "scheduler.h"

#include "utils.h"

#include <iostream>
#include <vector>
#include <map>


int main(){
    struct Kites::reorder::InstructionNode *node1=new Kites::reorder::InstructionNode();
    node1->instr=(0x3402829b);
     struct Kites::reorder::InstructionNode *node2=new Kites::reorder::InstructionNode();
     node2->instr=(0x0ab2b613);
     std::vector<struct Kites::reorder::InstructionNode *> instructions;
     instructions.push_back(node1);
     instructions.push_back(node2);
    std::vector<std::map<int,int>> sources(32);
    std::vector<std::map<int,int>> destinations(32);
    std::vector<std::map<int,int>>loadStores(32);
    makeGraph(instructions,sources,destinations,loadStores);
     std::cout<<Kites::reorder::checkDependecy(sources,destinations,loadStores,instructions,node1);
}