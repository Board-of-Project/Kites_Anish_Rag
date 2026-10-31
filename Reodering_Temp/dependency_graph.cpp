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

/*This file makes node of instructions from hex file and creates sources/destination table*/

// returns instruction node given its hex
struct Instruction_Node * Instruction_Decode(std::string hexcode,int index) {
    uint32_t instr = std::stoul(hexcode, nullptr, 16);

    int opcode = instr & 0x7F;

	// by default -1
    int rd  = -1;
    int rs1 = -1;
    int rs2 = -1;
	type Type;

	// identifying registers
    switch (opcode) {
        // R-type: add, sub, and, or, xor, sll, srl, etc.
        case 0x33:
        // R-type 64-bit variants (if applicable)
        case 0x3B:
            rd  = (instr >> 7)  & 0x1F;
            rs1 = (instr >> 15) & 0x1F;
            rs2 = (instr >> 20) & 0x1F;
			Type = type::R;
            break;

		// loads
		case 0x03:
			rd  = (instr >> 7)  & 0x1F;
            rs1 = (instr >> 15) & 0x1F;
			Type = type::ld;
			break;

        // I-type: immediate arithmetic
        case 0x13:
            rd  = (instr >> 7)  & 0x1F;
            rs1 = (instr >> 15) & 0x1F;
			Type = type::I;
            break;

        // S-type: stores
        case 0x23:
            rs1 = (instr >> 15) & 0x1F;
            rs2 = (instr >> 20) & 0x1F;
			Type = type::sd;
            break;

        // B-type: branches
        case 0x63:
            rs1 = (instr >> 15) & 0x1F;
            rs2 = (instr >> 20) & 0x1F;
			Type = type::branch;
            break;

        // U-type: lui, auipc
        case 0x37:
        case 0x17:
            rd = (instr >> 7) & 0x1F;
			Type = type::misc;
            break;

        // jal, jalr
		case 0x67:
        case 0x6F:
            rd = (instr >> 7) & 0x1F;
			Type = type::branch;
            break;

        // Other instructions: registers remain -1
        default:
            break;
    }

	// ignore x0
    if(rd==0){rd=-1;}
    if(rs1==0){rs1=-1;}
    if(rs2==0){rs2=-1;}
    struct Instruction_Node *N=new Instruction_Node();
    N->d=rd;
    N->s1=rs1;
    N->s2=rs2;
	N->Type=Type;
    N->idx=index;
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
        std::cerr << "Error: Could not open the hex file!" << std::endl;
    }
	
	std::vector <struct Instruction_Node*> curr_block;
	struct Instruction_Node* curr_instr;
    std::string line;
    int index=0;
    // read the file line by line
    while (std::getline(hexFile, line)) {
        if (line.empty()) continue;
        std::string Instruction=line.substr(2,8);
		curr_instr = Instruction_Decode(Instruction,index);

		// if branch and block size>0, push the block without the branch instruction
		if (curr_instr->Type==type::branch && curr_block.size()) {
			Instruction_blocks.push_back(curr_block);
			curr_block.clear();
		}

		curr_block.push_back(curr_instr);
        index+=1;
    }
	if (curr_block.size()) Instruction_blocks.push_back(curr_block);

    // Always close the stream
    hexFile.close();
    //making graph
}


// sources and destination table with 32 entries for each reg, stores instruction idx
void Make_Graph(std::vector<struct Instruction_Node *>& Instructions,std::vector<std::map<int,int> >&sources,std::vector<std::map<int,int> >&destination){
    for(struct Instruction_Node *N:Instructions){
        if(N->s1!=-1){
            sources[(N->s1)].insert({N->idx,N->idx});
        }
        if(N->s2!=-1){
            sources[(N->s2)].insert({N->idx,N->idx});
        }
        if(N->d!=-1){
            destination[(N->d)].insert({N->idx,N->idx});
        }
    }
}