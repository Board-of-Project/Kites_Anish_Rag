#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H

#include <string>
#include <vector>
#include <map>

struct Instruction_Node {
    int s1;
    int s2;
    int d;
    int type; // 0 if R, 1 if I, 2 if ld/sd, 3 if branch 
    int idx;
    int priority;
    int expected_index;
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
int Read_File(std::vector<struct Instruction_Node*>& Instructions);
void Make_Graph(std::vector<struct Instruction_Node*>& Instructions, 
                std::vector<std::map<int,int>>& soruces, 
               std::vector<std::map<int,int>>& destination);

#endif