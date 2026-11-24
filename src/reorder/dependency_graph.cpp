#include "dependency_graph.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <map>

namespace Kites::reorder{
struct InstructionNode *  instructionDecode(const uint32_t instruction, int index) {
    auto* node = new Kites::reorder::InstructionNode();
    node->instr = instruction;
    node->idx = index;
    int op = node->opcode();
    node->branchFlag=( op == 0x63 || op == 0x67 || op == 0x6F);

    return node;
}
// reads a given file and stores all instruction nodes in an array
int readFile(std::vector<struct Kites::reorder::InstructionNode *>& instructions, std::vector<uint32_t> &hexcodes){
    int lineCount = 0;
    int index=0;
    // read the file line by line
   for(uint32_t instruction:hexcodes) {
        lineCount++;
        instructions.push_back(instructionDecode(instruction,index));
        index+=1;
    }
    return 0;
}

void readFileForBranch(std::vector <std::vector <struct Kites::reorder::InstructionNode*> >& instructionBlocks, const std::vector<uint32_t> &hexcodes){
	std::vector <struct Kites::reorder::InstructionNode*> totalInstructions;
    std::string line;
    int index=0;
    // read the file line by line
   for(uint32_t instruction:hexcodes) {
        totalInstructions.push_back(instructionDecode(instruction,index));
        index+=1;
    }

    int n=totalInstructions.size();
    for(struct Kites::reorder::InstructionNode *node:totalInstructions){
        if(node->type()==(InstructionKind::Branch)&&(node->idx+(node->branchJump()/4)>=0)&&(node->idx+(node->branchJump()/4)<n)){
            totalInstructions[node->idx+(node->branchJump()/4)]->branchFlag=2;
        }
    }

	std::vector <struct Kites::reorder::InstructionNode*> currBlock;
    for(struct Kites::reorder::InstructionNode *node:totalInstructions){
		if (node->branchFlag && currBlock.size()) {
			instructionBlocks.push_back(currBlock);
			currBlock.clear();
		}

		currBlock.push_back(node);
    }
	if (currBlock.size()) instructionBlocks.push_back(currBlock);

}

// sources and destination table with 32 entries for each reg, stores instruction idx
void makeGraph(std::vector<struct Kites::reorder::InstructionNode *>& instructions,std::vector<std::map<int,int> >&sources,std::vector<std::map<int,int> >&destination
,std::vector<std::map<int,int> >&loadStores
){
    for(struct Kites::reorder::InstructionNode *node:instructions){
        if(node->s1()!=-1){
            sources[(node->s1())].insert({node->idx,node->idx});
        }
        if(node->s2()!=-1){
            sources[(node->s2())].insert({node->idx,node->idx});
        }
        if(node->d()!=-1){
            destination[(node->d())].insert({node->idx,node->idx});
        }
        if(node->type()==(InstructionKind::Ld)&&node->s1()>=0){
            loadStores[node->s1()].insert({node->idx,node->idx});
        }
        if(node->type()==(InstructionKind::Sd)&&node->s1()>=0){
            loadStores[node->s1()].insert({node->idx,node->idx});
        }
    }
}
}