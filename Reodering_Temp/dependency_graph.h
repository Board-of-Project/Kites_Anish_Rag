#ifndef DEPENDENCY_GRAPH_H
#define DEPENDENCY_GRAPH_H

#include <string>
#include <vector>
#include <map>

enum class type {R, ld, sd, branch, misc, I};

struct Instruction_Node {
    int s1;
    int s2;
    int d;
    type Type;
    int branch_flag;
    int branch_jump;
    int idx;
    int priority;
    int expected_index;
    int imm;
    int last_touched_s1;
    int size;
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
struct Instruction_Node* Instruction_Decode(std::string hexcode, int index);
int Read_File(std::vector<struct Instruction_Node*>& Instructions, std::string input_filename="instructions.hex");
void Read_File_for_branch(std::vector <std::vector <struct Instruction_Node*> >& Instruction_blocks, std::string input_filename="instructions.hex");
void Make_Graph(std::vector<struct Instruction_Node*>& Instructions, 
                std::vector<std::map<int,int>>& soruces, 
               std::vector<std::map<int,int>>& destination,
               std::vector<std::map<int,int>>& load_stores
            );

#endif