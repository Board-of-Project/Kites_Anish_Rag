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
// Sign-extend a value that is 'bits' wide to a 32-bit signed int
static inline int32_t sign_extend(uint32_t value, int bits) {
    int shift = 32 - bits;
    return (int32_t)(value << shift) >> shift;
}

struct Instruction_Node * Instruction_Decode(std::string hexcode, int index) {
    uint32_t instr = std::stoul(hexcode, nullptr, 16);

    int opcode = instr & 0x7F;

    // by default -1
    int rd  = -1;
    int rs1 = -1;
    int rs2 = -1;
    type Type = type::misc;      // default so it's never uninitialized

    int branch_flag = 0;
    int branch_jump = 0;

    // identifying registers
    switch (opcode) {
        // R-type
        case 0x33:
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

        // B-type: conditional branches
        case 0x63: {
            rs1 = (instr >> 15) & 0x1F;
            rs2 = (instr >> 20) & 0x1F;
            Type = type::branch;

            // imm[12|10:5|4:1|11], bit 0 is always 0
            uint32_t imm = (((instr >> 31) & 0x1)  << 12) |
                           (((instr >> 7)  & 0x1)  << 11) |
                           (((instr >> 25) & 0x3F) << 5)  |
                           (((instr >> 8)  & 0xF)  << 1);
            branch_flag = 1;
            branch_jump = sign_extend(imm, 13);
            break;
        }

        // U-type: lui, auipc
        case 0x37:
        case 0x17:
            rd = (instr >> 7) & 0x1F;
            Type = type::misc;
            break;

        // jalr (I-format immediate)
        case 0x67:
            rd  = (instr >> 7)  & 0x1F;
            rs1 = (instr >> 15) & 0x1F;   // jalr reads rs1 as the base address
            Type = type::branch;
            branch_flag = 1;
            branch_jump = (int32_t)instr >> 20;   // imm[11:0], sign-extended
            break;

        // jal (J-format immediate)
        case 0x6F: {
            rd = (instr >> 7) & 0x1F;
            Type = type::branch;

            // imm[20|10:1|11|19:12], bit 0 is always 0
            uint32_t imm = (((instr >> 31) & 0x1)   << 20) |
                           (((instr >> 12) & 0xFF)  << 12) |
                           (((instr >> 20) & 0x1)   << 11) |
                           (((instr >> 21) & 0x3FF) << 1);
            branch_flag = 1;
            branch_jump = sign_extend(imm, 21);
            break;
        }

        // Other instructions: registers remain -1
        default:
            break;
    }

    // ignore x0
    if (rd  == 0) { rd  = -1; }
    if (rs1 == 0) { rs1 = -1; }
    if (rs2 == 0) { rs2 = -1; }

    struct Instruction_Node *N = new Instruction_Node();
    N->d   = rd;
    N->s1  = rs1;
    N->s2  = rs2;
    N->Type = Type;
    N->idx = index;
    N->branch_flag = branch_flag;
    N->branch_jump = branch_jump;
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
	
	std::vector <struct Instruction_Node*> Total_Instructions;;
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
        if(I->Type==(type::branch)&&(I->idx+(I->branch_jump/4)>=0)&&(I->idx+(I->branch_jump/4)<n)){
            Total_Instructions[I->idx+(I->branch_jump/4)]->branch_flag=2;
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