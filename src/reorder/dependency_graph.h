#ifndef DEPENDENCY_GRAPH_H
#define DEPENDENCY_GRAPH_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>

static inline int32_t signExtend(uint32_t value, int bits) {
    int shift = 32 - bits;
    return (int32_t)(value << shift) >> shift;
}
enum class InstructionKind {R, Ld, Sd, Branch, Misc, I};
namespace Kites::reorder{

struct InstructionNode {
    // ---- stored fields ----
    uint32_t instr = 0;          // raw encoding
    int32_t  idx = 0;
    std::vector<double> priority;
    int32_t  expectedIndex = 0;
    int32_t  lastTouchedS1 = -1;
    bool branchFlag;
    // ---- decoded on demand ----
    int opcode() const { return instr & 0x7F; }
    int funct3() const { return (instr >> 12) & 7; }

    InstructionKind type() const {
        switch (opcode()) {
            case 0x33: case 0x3B: return InstructionKind::R;
            case 0x03:            return InstructionKind::Ld;
            case 0x13:            return InstructionKind::I;
            case 0x23:            return InstructionKind::Sd;
            case 0x63: case 0x67: case 0x6F: return InstructionKind::Branch;
            default:              return InstructionKind::Misc;
        }
    }

    int d() const {
        switch (opcode()) {
            case 0x33: case 0x3B: case 0x03: case 0x13:
            case 0x37: case 0x17: case 0x67: case 0x6F: case 0x1B:{
                int r = (instr >> 7) & 0x1F;
                return r ? r : -1;
            }
            default: return -1;
        }
    }

    int s1() const {
        switch (opcode()) {
            case 0x33: case 0x3B: case 0x03: case 0x13:
            case 0x23: case 0x63: case 0x67: case 0x1B:{
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
            case 0x03: return signExtend(instr >> 20, 12);
            case 0x23: return signExtend(((instr >> 25) << 5) | ((instr >> 7) & 0x1F), 12);
            default:   return 0;
        }
    }

    int branchJump() const {
        switch (opcode()) {
            case 0x63: {
                uint32_t i = (((instr >> 31) & 0x1)  << 12) |
                             (((instr >> 7)  & 0x1)  << 11) |
                             (((instr >> 25) & 0x3F) << 5)  |
                             (((instr >> 8)  & 0xF)  << 1);
                return signExtend(i, 13);
            }
            case 0x67: return (int32_t)instr >> 20;
            case 0x6F: {
                uint32_t i = (((instr >> 31) & 0x1)   << 20) |
                             (((instr >> 12) & 0xFF)  << 12) |
                             (((instr >> 20) & 0x1)   << 11) |
                             (((instr >> 21) & 0x3FF) << 1);
                return signExtend(i, 21);
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
struct CompareInstructions {
    // Both arguments must be pointers, and the function MUST be marked const
    bool operator()(const InstructionNode* a, const InstructionNode* b) const {
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
struct InstructionNode* instructionDecode(const uint32_t instruction, int index);
int readFile(std::vector<struct Kites::reorder::InstructionNode*>& instructions, std::vector<uint32_t>&hexcodes);
void readFileForBranch(std::vector <std::vector <struct Kites::reorder::InstructionNode*> >& instructionBlocks, const std::vector<uint32_t>&hexcodes);
void makeGraph(std::vector<struct Kites::reorder::InstructionNode*>& instructions, 
                std::vector<std::map<int,int>>& soruces, 
               std::vector<std::map<int,int>>& destination,
               std::vector<std::map<int,int>>& loadStores
            );
}
#endif