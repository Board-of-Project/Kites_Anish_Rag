#include "graphmaker.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <map>

struct Instruction_Node * Instruction_Decode(std::string hexcode,int index) {
    uint32_t instr = std::stoul(hexcode, nullptr, 16);

    int opcode = instr & 0x7F;

    int rd  = -1;
    int  rs1 = -1;
    int rs2 = -1;

    switch (opcode) {
        // R-type: add, sub, and, or, xor, sll, srl, etc.
        case 0x33:
        // R-type 64-bit variants (if applicable)
        case 0x3B:
            rd  = (instr >> 7)  & 0x1F;
            rs1 = (instr >> 15) & 0x1F;
            rs2 = (instr >> 20) & 0x1F;
            break;

        // I-type: loads, immediate arithmetic, jalr
        case 0x03:
        case 0x13:
        case 0x67:
            rd  = (instr >> 7)  & 0x1F;
            rs1 = (instr >> 15) & 0x1F;
            break;

        // S-type: stores
        case 0x23:
            rs1 = (instr >> 15) & 0x1F;
            rs2 = (instr >> 20) & 0x1F;
            break;

        // B-type: branches
        case 0x63:
            rs1 = (instr >> 15) & 0x1F;
            rs2 = (instr >> 20) & 0x1F;
            break;

        // U-type: lui, auipc
        case 0x37:
        case 0x17:
            rd = (instr >> 7) & 0x1F;
            break;

        // J-type: jal
        case 0x6F:
            rd = (instr >> 7) & 0x1F;
            break;

        // Other instructions: registers remain -1
        default:
            break;
    }
    if(rd==0){rd=-1;}
    if(rs1==0){rs1=-1;}
    if(rs2==0){rs2=-1;}
    struct Instruction_Node *N=new Instruction_Node();
    N->d=rd;
    N->s1=rs1;
    N->s2=rs2;
    N->idx=index;
    return N;
}

int Read_File(std::vector<struct Instruction_Node *>& Instructions){
    std::ifstream hexFile("instructions.hex"); 
    if (!hexFile.is_open()) {
        std::cerr << "Error: Could not open the hex file!" << std::endl;
        return 1;
    }

    std::string line;
    int lineCount = 0;
    int index=0;
    // 2. Read the file line by line
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

void Make_Graph(std::vector<struct Instruction_Node *>& Instructions,std::vector<std::map<int,int> >&soruces,std::vector<std::map<int,int> >&destination){
    for(struct Instruction_Node *N:Instructions){
        if(N->s1!=-1){
            soruces[(N->s1)].insert({N->idx,N->idx});
        }
        if(N->s2!=-1){
            soruces[(N->s2)].insert({N->idx,N->idx});
        }
        if(N->d!=-1){
            destination[(N->d)].insert({N->idx,N->idx});
        }
    }
}