#include "dependency_graph.h"
#include "scheduler.h"
#include "heuristic.h"
#include "utils.h"
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>



//check if free
bool Check_Dependecy(
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    struct Instruction_Node * I
){
    int source=I->s1;
    if(source==-1||destinations[source].empty()||destinations[source].begin()->first>=I->idx){
        source=I->s2;
        if(source==-1||destinations[source].empty()||destinations[source].begin()->first>=I->idx){
            int destination=I->d;
            if(destination==-1||sources[destination].empty()||sources[destination].begin()->first>=I->idx){
                return true;
            }
        }
    }
    return false;
}

void Initialize(std::priority_queue<struct Instruction_Node *,std::vector<struct Instruction_Node *>,Compare_Instructions> &Priority_List,
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations
){
    for(int i=0;i<Instructions.size();i+=1){
        if(Check_Dependecy(sources,destinations,Instructions[i])){
            Priority_List.push(Instructions[i]);
        }
    }
}

// not-ready list to waitlist transfer
void Update_Children(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<struct Instruction_Node *> &Wait_List,
    struct Instruction_Node *I,
    int Executed_Including_Nop
){

    if(I->s1!=-1 && !destinations[I->s1].empty()){
        for(const auto & child:destinations[I->s1]){
            if(child.first>I->idx){
                int expected=Executed_Including_Nop+Nops_Needed(I,Instructions[child.first]);
                Instructions[child.first]->expected_index=std::max(expected,Instructions[child.first]->expected_index);
                if(Check_Dependecy(sources,destinations,Instructions[child.first])){
                    Wait_List.push_back(Instructions[child.first]);
                }
            }
        }
    }
    if(I->s2!=-1 && !destinations[I->s2].empty()){
        for(const auto & child:destinations[I->s2]){
            if(child.first>I->idx){
                int expected=Executed_Including_Nop+Nops_Needed(I,Instructions[child.first]);
                Instructions[child.first]->expected_index=std::max(expected,Instructions[child.first]->expected_index);
                if(Check_Dependecy(sources,destinations,Instructions[child.first])){
                    Wait_List.push_back(Instructions[child.first]);
                }
            }
        }
    }
    if(I->d!=-1 && !sources[I->d].empty()){
        for(const auto & child:sources[I->d]){
            if(child.first>I->idx){
                int expected=Executed_Including_Nop+Nops_Needed(I,Instructions[child.first]);
                Instructions[child.first]->expected_index=std::max(expected,Instructions[child.first]->expected_index);
                if(Check_Dependecy(sources,destinations,Instructions[child.first])){
                    Wait_List.push_back(Instructions[child.first]);
                }
            }
        }
    }    
}

// schedules the instructions and stores in the array passed
void Scheduler(std::vector<int>&Final_Instructions, std::string input_filename) {
    // std::vector<struct Instruction_Node *> Instructions;
    // Read_File(Instructions);
	std::vector <std::vector <struct Instruction_Node*>> Instruction_blocks;
	Read_File_for_branch(Instruction_blocks, input_filename);
	// prints the number of hazards
	Num_Hazards(Instruction_blocks);
	int Executed_Including_NOP=0;
	for (std::vector <struct Instruction_Node*> Instructions: Instruction_blocks) {
		if(Instructions.size()==0){
            continue;
        }
		// check if the first instruction is branch
		if (Instructions[0]->Type==type::branch) {
			Final_Instructions.push_back(Instructions[0]->idx);
			Instructions.erase(Instructions.begin());
		}
		if(Instructions.size()==0){
            continue;
        }
        int index1=Instructions[0]->idx;
        for(struct Instruction_Node * I:Instructions){
            I->idx=I->idx-index1;
        }
		std::vector<std::map<int,int>> sources(32);
		std::vector<std::map<int,int>> destinations(32);
		Make_Graph(Instructions,sources,destinations);

		//Heuristic of choice
    	Heuristic1(Instructions,sources,destinations);

		std::priority_queue<struct Instruction_Node *,std::vector<struct Instruction_Node *>,Compare_Instructions> Priority_List;
		std::vector<struct Instruction_Node *> Wait_List;
		Initialize(Priority_List,Instructions,sources,destinations);
		int Executed=0;
		int N=Instructions.size();
		while(Executed<N){
			Executed_Including_NOP+=1;
			if(!Priority_List.empty()){
				Executed+=1;
				struct Instruction_Node * I=Priority_List.top();
				Final_Instructions.push_back(I->idx+index1);
				Priority_List.pop(); // pluck an instruction
				std::cout<<"Executed "<<I->idx+index1+1<<"\n";
				if(I->s1!=-1){sources[I->s1].erase(I->idx);}
				if(I->s2!=-1){sources[I->s2].erase(I->idx);}
				if(I->d!=-1){destinations[I->d].erase(I->idx);}
				
				Update_Children(Instructions,sources,destinations,Wait_List,I,Executed_Including_NOP);
			}
			else{
				Final_Instructions.push_back(-1);
			}
			// Pushing ready ones from waitlist into prority queue
			for(int i=0;i<Wait_List.size();i+=1){
				struct Instruction_Node *I=Wait_List[i];
				if(I->expected_index<=Executed_Including_NOP){
					Priority_List.push(I);
					Wait_List.erase(Wait_List.begin()+i);
				}
			}
		}
	}
}
