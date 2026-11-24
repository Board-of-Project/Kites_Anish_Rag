#include "dependency_graph.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <map>

namespace Kites::Reorder{
struct Instruction_Node *  Instruction_Decode(const uint32_t instruction, int index) {
    auto* N = new Kites::Reorder::Instruction_Node();
    N->instr = instruction;
    N->idx = index;
    int op = N->opcode();
    N->branch_flag=( op == 0x63 || op == 0x67 || op == 0x6F);

    return N;
}
// reads a given file and stores all instruction nodes in an array
int Read_File(std::vector<struct Kites::Reorder::Instruction_Node *>& Instructions, std::vector<uint32_t> &Hexcodes){
    int lineCount = 0;
    int index=0;
    // read the file line by line
   for(uint32_t Instruction:Hexcodes) {
        lineCount++;
        Instructions.push_back(Instruction_Decode(Instruction,index));
        index+=1;
    }
    return 0;
}

void Read_File_for_branch(std::vector <std::vector <struct Kites::Reorder::Instruction_Node*> >& Instruction_blocks, const std::vector<uint32_t> &Hexcodes){
	std::vector <struct Kites::Reorder::Instruction_Node*> Total_Instructions;
    std::string line;
    int index=0;
    // read the file line by line
   for(uint32_t Instruction:Hexcodes) {
        Total_Instructions.push_back(Instruction_Decode(Instruction,index));
        index+=1;
    }

    int n=Total_Instructions.size();
    for(struct Kites::Reorder::Instruction_Node *I:Total_Instructions){
        if(I->Type()==(type::branch)&&(I->idx+(I->branch_jump()/4)>=0)&&(I->idx+(I->branch_jump()/4)<n)){
            Total_Instructions[I->idx+(I->branch_jump()/4)]->branch_flag=2;
        }
    }

	std::vector <struct Kites::Reorder::Instruction_Node*> curr_block;
    for(struct Kites::Reorder::Instruction_Node *I:Total_Instructions){
		if (I->branch_flag && curr_block.size()) {
			Instruction_blocks.push_back(curr_block);
			curr_block.clear();
		}

		curr_block.push_back(I);
    }
	if (curr_block.size()) Instruction_blocks.push_back(curr_block);

}

// sources and destination table with 32 entries for each reg, stores instruction idx
void Make_Graph(std::vector<struct Kites::Reorder::Instruction_Node *>& Instructions,std::vector<std::map<int,int> >&sources,std::vector<std::map<int,int> >&destination
,std::vector<std::map<int,int> >&load_stores
){
    for(struct Kites::Reorder::Instruction_Node *N:Instructions){
        if(N->s1()!=-1){
            sources[(N->s1())].insert({N->idx,N->idx});
        }
        if(N->s2()!=-1){
            sources[(N->s2())].insert({N->idx,N->idx});
        }
        if(N->d()!=-1){
            destination[(N->d())].insert({N->idx,N->idx});
        }
        if(N->Type()==(type::ld)&&N->s1()>=0){
            load_stores[N->s1()].insert({N->idx,N->idx});
        }
        if(N->Type()==(type::sd)&&N->s1()>=0){
            load_stores[N->s1()].insert({N->idx,N->idx});
        }
    }
}
}