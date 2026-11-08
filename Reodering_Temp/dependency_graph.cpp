#include "dependency_graph.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <map>

Instruction_Node* Instruction_Decode(const std::string& hexcode, int index) {
    auto* N = new Instruction_Node();
    N->instr = (uint32_t)std::stoul(hexcode, nullptr, 16);
    N->idx = index;
    int op = N->opcode();
    N->branch_flag=( op == 0x63 || op == 0x67 || op == 0x6F);

    return N;
}
// reads a given file and stores all instruction nodes in an array
int Read_File(std::vector<struct Instruction_Node *>& Instructions, std::string input_filename){
    std::ifstream hexFile(input_filename);
    if (!hexFile.is_open()) {
        std::cerr << "Error: Could not open the hex file!" << std::endl;
        return 1;
    }

    std::string line;
    int lineCount = 0;
    int index=0;
    // read the file line by line
    while (std::getline(hexFile, line)) {
        lineCount++;

        if (line.empty()) continue;
        std::string Instruction=line.substr(2,8);
        int rs1,rs2,rd;
        Instructions.push_back(Instruction_Decode(Instruction,index));
        index+=1;
    }

    // 4. Always close the stream
    hexFile.close();
    //making graph
    return 0;
}

void Read_File_for_branch(std::vector <std::vector <struct Instruction_Node*> >& Instruction_blocks, std::string input_filename){
    std::ifstream hexFile(input_filename);
    if (!hexFile.is_open()) {
        std::cerr << "Error: Could not open the hex file_1!" << std::endl;
    }
	
	std::vector <struct Instruction_Node*> Total_Instructions;
    std::string line;
    int index=0;
    // read the file line by line
    while (std::getline(hexFile, line)) {
        if (line.empty()) continue;
        std::string Instruction=line.substr(2,8);
        Total_Instructions.push_back(Instruction_Decode(Instruction,index));
        index+=1;
    }

    // Always close the stream
    hexFile.close();
    int n=Total_Instructions.size();
    for(struct Instruction_Node *I:Total_Instructions){
        if(I->Type()==(type::branch)&&(I->idx+(I->branch_jump()/4)>=0)&&(I->idx+(I->branch_jump()/4)<n)){
            Total_Instructions[I->idx+(I->branch_jump()/4)]->branch_flag=2;
        }
    }

	std::vector <struct Instruction_Node*> curr_block;
    for(struct Instruction_Node *I:Total_Instructions){
		if (I->branch_flag && curr_block.size()) {
			Instruction_blocks.push_back(curr_block);
			curr_block.clear();
		}

		curr_block.push_back(I);
    }
	if (curr_block.size()) Instruction_blocks.push_back(curr_block);

}

// sources and destination table with 32 entries for each reg, stores instruction idx
void Make_Graph(std::vector<struct Instruction_Node *>& Instructions,std::vector<std::map<int,int> >&sources,std::vector<std::map<int,int> >&destination
,std::vector<std::map<int,int> >&load_stores
){
    for(struct Instruction_Node *N:Instructions){
        if(N->s1()!=-1){
            sources[(N->s1())].insert({N->idx,N->idx});
        }
        if(N->s2()!=-1){
            sources[(N->s2())].insert({N->idx,N->idx});
        }
        if(N->d()!=-1){
            destination[(N->d())].insert({N->idx,N->idx});
        }
        if(N->Type()==(type::ld)){
            load_stores[N->s1()].insert({N->idx,N->idx});
        }
        if(N->Type()==(type::sd)){
            load_stores[N->s1()].insert({N->idx,N->idx});
        }
    }
}