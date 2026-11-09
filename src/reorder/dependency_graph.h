#ifndef DEPENDENCY_GRAPH_H
#define DEPENDENCY_GRAPH_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>

static inline int32_t sign_extend(uint32_t value, int bits) {
    int shift = 32 - bits;
    return (int32_t)(value << shift) >> shift;
}
enum class type {R, ld, sd, branch, misc, I};
namespace Kites::Reorder{

struct Instruction_Node {
    // ---- stored fields ----
    uint32_t instr = 0;          // raw encoding
    int32_t  idx = 0;
    int32_t  priority = 0;
    int32_t  expected_index = 0;
    int32_t  last_touched_s1 = -1;
    bool branch_flag;
    // ---- decoded on demand ----
    int opcode() const { return instr & 0x7F; }
    int funct3() const { return (instr >> 12) & 7; }

    type Type() const {
        switch (opcode()) {
            case 0x33: case 0x3B: return type::R;
            case 0x03:            return type::ld;
            case 0x13:            return type::I;
            case 0x23:            return type::sd;
            case 0x63: case 0x67: case 0x6F: return type::branch;
            default:              return type::misc;
        }
    }

    int d() const {
        switch (opcode()) {
            case 0x33: case 0x3B: case 0x03: case 0x13:
            case 0x37: case 0x17: case 0x67: case 0x6F: {
                int r = (instr >> 7) & 0x1F;
                return r ? r : -1;
            }
            default: return -1;
        }
    }

    int s1() const {
        switch (opcode()) {
            case 0x33: case 0x3B: case 0x03: case 0x13:
            case 0x23: case 0x63: case 0x67: {
                int r = (instr >> 15) & 0x1F;
                return r ? r : -1;
            }
            default: return -1;
        }
    }

    int s2() const {
        switch (opcode()) {
            case 0x33: case 0x3B: case 0x23: case 0x63: {
                int r = (instr >> 20) & 0x1F;
                return r ? r : -1;
            }
            default: return -1;
        }
    }

    int imm() const {
        switch (opcode()) {
            case 0x03: return sign_extend(instr >> 20, 12);
            case 0x23: return sign_extend(((instr >> 25) << 5) | ((instr >> 7) & 0x1F), 12);
            default:   return 0;
        }
    }

    int branch_jump() const {
        switch (opcode()) {
            case 0x63: {
                uint32_t i = (((instr >> 31) & 0x1)  << 12) |
                             (((instr >> 7)  & 0x1)  << 11) |
                             (((instr >> 25) & 0x3F) << 5)  |
                             (((instr >> 8)  & 0xF)  << 1);
                return sign_extend(i, 13);
            }
            case 0x67: return (int32_t)instr >> 20;
            case 0x6F: {
                uint32_t i = (((instr >> 31) & 0x1)   << 20) |
                             (((instr >> 12) & 0xFF)  << 12) |
                             (((instr >> 20) & 0x1)   << 11) |
                             (((instr >> 21) & 0x3FF) << 1);
                return sign_extend(i, 21);
            }
            default: return 0;
        }
    }

    int size() const {
        switch (funct3() & 3) {
            case 0: return 1;
            case 1: return 2;
            case 2: return 4;
            default: return 8;
        }
    }
};

// Custom comparator for pointers
struct Compare_Instructions {
    // Both arguments must be pointers, and the function MUST be marked const
    bool operator()(const Instruction_Node* a, const Instruction_Node* b) const {
        // Always add a safety check for null pointers if applicable
        if (!a || !b) return false; 
        
        // Max-heap: highest grade at the top
        if(a->priority<b->priority){
            return true;
        }
        else if(a->priority==b->priority){
            return a->idx>b->idx;
        }
        else{
            return false;
        }
        // Min-heap: lowest grade at the top
        // return a->grade < b->grade;
    }
};

// Function declarations
struct Instruction_Node* Instruction_Decode(const uint32_t instruction, int index);
int Read_File(std::vector<struct Kites::Reorder::Instruction_Node*>& Instructions, std::vector<uint32_t>&Hexcodes);
void Read_File_for_branch(std::vector <std::vector <struct Kites::Reorder::Instruction_Node*> >& Instruction_blocks, const std::vector<uint32_t>&Hexcodes);
void Make_Graph(std::vector<struct Kites::Reorder::Instruction_Node*>& Instructions, 
                std::vector<std::map<int,int>>& soruces, 
               std::vector<std::map<int,int>>& destination,
               std::vector<std::map<int,int>>& load_stores
            );
}
#endif