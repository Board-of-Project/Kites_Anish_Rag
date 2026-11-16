#include "dependency_graph.h"
#include "scheduler.h"

#include "utils.h"

#include <iostream>
#include <vector>
#include <map>


int main(){
    struct Kites::Reorder::Instruction_Node *I1=new Kites::Reorder::Instruction_Node();
    I1->instr=(0x3402829b);
     struct Kites::Reorder::Instruction_Node *I2=new Kites::Reorder::Instruction_Node();
     I2->instr=(0x0ab2b613);
     std::vector<struct Kites::Reorder::Instruction_Node *> Instructions;
     Instructions.push_back(I1);
     Instructions.push_back(I2);
    std::vector<std::map<int,int>> sources(32);
    std::vector<std::map<int,int>> destinations(32);
    std::vector<std::map<int,int>>load_stores(32);
    Make_Graph(Instructions,sources,destinations,load_stores);
     std::cout<<Kites::Reorder::Check_Dependecy(sources,destinations,load_stores,Instructions,I1);
}