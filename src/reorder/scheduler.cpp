#include "dependency_graph.h"
#include "scheduler.h"
#include "heuristic.h"
#include "utils.h"
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
#include <set>

namespace Kites::Reorder{
//check if free
bool Check_Dependecy(
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<std::map<int,int> >&load_stores,
    std::vector<struct Instruction_Node *>&Instructions,
    struct Instruction_Node * I
){
    if(I->Type()==(type::ld)){
        //WAR in mem
        if(I->s1()!=-1){
        for(const auto & child:load_stores[I->s1()]){
            int index=child.first;
            if(index>=I->idx){
                break;
            }
            if(Instructions[index]->Type()==(type::sd)){
                struct Instruction_Node * I2=Instructions[index];
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    return false;
                }
            }
        }
        }
        else{
            for(struct Kites::Reorder::Instruction_Node *I2:Instructions){
                if(I2->idx>=I->idx){break;}
                if(I2->Type()==(type::sd)){
                    if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    return false;
                }
                }
            }
        }
    }
    if(I->Type()==(type::sd)){
        //WAW in mem
        if(I->s1()!=-1){
        for(const auto & child:load_stores[I->s1()]){
            int index=child.first;
            if(index>=I->idx){
                break;
            }
            if(Instructions[index]->Type()==(type::sd)){
                struct Instruction_Node * I2=Instructions[index];
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    return false;
                }
            }
        }
        //RAW in mem
        for(const auto & child:load_stores[I->s1()]){
            int index=child.first;
            if(index>=I->idx){
                break;
            }
            if(Instructions[index]->Type()==(type::ld)){
                struct Instruction_Node * I2=Instructions[index];
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    return false;
                }
            }
        }
    }
    else{
        for(struct Kites::Reorder::Instruction_Node *I2:Instructions){
            if(I2->idx>=I->idx){break;}
            if(I2->Type()==(type::sd)||I2->Type()==(type::ld)){
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                return false;
            }
            }
        }
    }
    }
    int source=I->s1();
    if(source==-1||destinations[source].empty()||destinations[source].begin()->first>=I->idx){
        source=I->s2();
        if(source==-1||destinations[source].empty()||destinations[source].begin()->first>=I->idx){
            int destination=I->d();
            if(destination==-1||sources[destination].empty()||sources[destination].begin()->first>=I->idx){
                if(destination==-1||destinations[destination].empty()||destinations[destination].begin()->first>=I->idx){
                    return true;
            }
            }
        }
    }
    return false;
}

void Initialize(std::priority_queue<struct Instruction_Node *,std::vector<struct Instruction_Node *>,Compare_Instructions> &Priority_List,
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<std::map<int,int> >&load_stores
){
    for(int i=0;i<Instructions.size();i+=1){
        if(Kites::Reorder::Check_Dependecy(sources,destinations,load_stores,Instructions,Instructions[i])){
            Priority_List.push(Instructions[i]);
        }
    }
}

// not-ready list to waitlist transfer
void Update_Children(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::set<struct Instruction_Node *> &Wait_List,
    std::vector<std::map<int,int>> &load_stores,
    struct Instruction_Node *I,
    int Executed_Including_Nop,
    Kites::Reorder::Proc p
){
    //WAR in reg for rs1
    if(I->s1()!=-1 && !destinations[I->s1()].empty()){
        for(const auto & child:destinations[I->s1()]){
            if(child.first>I->idx){
                int expected=Executed_Including_Nop+Nops_Needed(I,Instructions[child.first],p);
                Instructions[child.first]->expected_index=std::max(expected,Instructions[child.first]->expected_index);
                if(Check_Dependecy(sources,destinations,load_stores,Instructions,Instructions[child.first])){
                    Wait_List.insert(Instructions[child.first]);
                }
            }
        }
    }
    //WAR in reg for rs2
    if(I->s2()!=-1 && !destinations[I->s2()].empty()){
        for(const auto & child:destinations[I->s2()]){
            if(child.first>I->idx){
                int expected=Executed_Including_Nop+Nops_Needed(I,Instructions[child.first],p);
                Instructions[child.first]->expected_index=std::max(expected,Instructions[child.first]->expected_index);
                if(Check_Dependecy(sources,destinations,load_stores,Instructions,Instructions[child.first])){
                    Wait_List.insert(Instructions[child.first]);
                }
            }
        }
    }
    //RAW in reg
    if(I->d()!=-1 && !sources[I->d()].empty()){
        for(const auto & child:sources[I->d()]){
            if(child.first>I->idx){
                int expected=Executed_Including_Nop+Nops_Needed(I,Instructions[child.first],p);
                Instructions[child.first]->expected_index=std::max(expected,Instructions[child.first]->expected_index);
                if(Check_Dependecy(sources,destinations,load_stores,Instructions,Instructions[child.first])){
                    Wait_List.insert(Instructions[child.first]);
                }
            }
        }
    }  
    //WAW in reg
    if(I->d()!=-1 && !destinations[I->d()].empty()){
        for(const auto & child:destinations[I->d()]){
            if(child.first>I->idx){
                int expected=Executed_Including_Nop+Nops_Needed(I,Instructions[child.first],p);
                Instructions[child.first]->expected_index=std::max(expected,Instructions[child.first]->expected_index);
                if(Check_Dependecy(sources,destinations,load_stores,Instructions,Instructions[child.first])){
                    Wait_List.insert(Instructions[child.first]);
                }
            }
        }
    }
    
    //IF load or store checking for mem
    if(I->Type()==(type::ld)&&I->s1()!=-1){
        //WAR
        for(const auto & child:load_stores[I->s1()]){
            if(child.first>I->idx&&Instructions[child.first]->Type()==(type::sd)){
                struct Instruction_Node *I2=Instructions[child.first];
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    int expected=Executed_Including_Nop+Nops_Needed(I,I2,p);
                    I2->expected_index=std::max(expected,I2->expected_index);
                    if(Check_Dependecy(sources,destinations,load_stores,Instructions,I2)){
                        Wait_List.insert(I2);
                    }
                }
            }
        }
    }

    if(I->Type()==(type::sd)&&I->s1()!=-1){
        //WAW
        for(const auto & child:load_stores[I->s1()]){
            if(child.first>I->idx&&Instructions[child.first]->Type()==(type::sd)){
                struct Instruction_Node *I2=Instructions[child.first];
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    int expected=Executed_Including_Nop+Nops_Needed(I,I2,p);
                    I2->expected_index=std::max(expected,I2->expected_index);
                    if(Check_Dependecy(sources,destinations,load_stores,Instructions,I2)){
                        Wait_List.insert(I2);
                    }
                }
            }
        }
        //RAW
        for(const auto & child:load_stores[I->s1()]){
            if(child.first>I->idx&&Instructions[child.first]->Type()==(type::ld)){
                struct Instruction_Node *I2=Instructions[child.first];
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    int expected=Executed_Including_Nop+Nops_Needed(I,I2,p);
                    I2->expected_index=std::max(expected,I2->expected_index);
                    if(Check_Dependecy(sources,destinations,load_stores,Instructions,I2)){
                        Wait_List.insert(I2);
                    }
                }
            }
        }
    }
    //waw or raw x0
    if((I->Type()==(type::sd))&&I->s1()==-1){
        for(struct Kites::Reorder::Instruction_Node *I2: Instructions){
            if(I2->idx>I->idx&&(I2->Type()==(type::sd)||I2->Type()==(type::ld))){
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    int expected=Executed_Including_Nop+Nops_Needed(I,I2,p);
                    I2->expected_index=std::max(expected,I2->expected_index);
                    if(Check_Dependecy(sources,destinations,load_stores,Instructions,I2)){
                        Wait_List.insert(I2);
                    }
                }
            }
        }
    }
    //war x0
    if((I->Type()==(type::ld))&&I->s1()==-1){
        for(struct Kites::Reorder::Instruction_Node *I2: Instructions){
            if(I2->idx>I->idx&&I2->Type()==(type::sd)){
                if(!(I->s1()==I2->s1()&&(!overlap(I->imm()+I->size(),I2->imm()+I2->size(),I->imm(),I2->imm()))&&I->last_touched_s1==I2->last_touched_s1)){
                    int expected=Executed_Including_Nop+Nops_Needed(I,I2,p);
                    I2->expected_index=std::max(expected,I2->expected_index);
                    if(Check_Dependecy(sources,destinations,load_stores,Instructions,I2)){
                        Wait_List.insert(I2);
                    }
                }
            }
        }
    }
}

// schedules the instructions and stores in the array passed
void Scheduler(std::vector<int>&Final_Instructions, const std::vector<uint32_t>&Hexcodes,Kites::Reorder::Proc processor,Kites::Reorder::HeuristicEntry H) {
    // std::vector<struct Instruction_Node *> Instructions;
    // Read_File(Instructions);
	std::vector <std::vector <struct Instruction_Node*>> Instruction_blocks;
	Read_File_for_branch(Instruction_blocks,Hexcodes);
	// prints the number of hazards
	Num_Hazards(Instruction_blocks,processor);
	int Executed_Including_NOP=0;
	for (std::vector <struct Instruction_Node*> Instructions: Instruction_blocks) {
		if(Instructions.size()==0){
            continue;
        }
		// check if the first instruction is branch
		if (Instructions[0]->branch_flag) {
			Final_Instructions.push_back(Instructions[0]->idx);
			Instructions.erase(Instructions.begin());
		}
		if(Instructions.size()==0){
            continue;
        }
        int index1=Instructions[0]->idx;
        std::vector<int> last_touched(32,-1);
        for(struct Instruction_Node * I:Instructions){
            I->idx=I->idx-index1;
            if(I->d()>=0){last_touched[I->d()]=I->idx;}
            if(I->s1()>=0){I->last_touched_s1=last_touched[I->s1()];}
        }
		std::vector<std::map<int,int>> sources(32);
		std::vector<std::map<int,int>> destinations(32);
        std::vector<std::map<int,int>>load_stores(32);
		Make_Graph(Instructions,sources,destinations,load_stores);

		//Heuristic of choice
    	H.fn(Instructions,sources,destinations,processor);

		std::priority_queue<struct Instruction_Node *,std::vector<struct Instruction_Node *>,Compare_Instructions> Priority_List;
		std::set<struct Instruction_Node *> Wait_List;
		Initialize(Priority_List,Instructions,sources,destinations,load_stores);
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
				if(I->s1()!=-1){sources[I->s1()].erase(I->idx);}
				if(I->s2()!=-1){sources[I->s2()].erase(I->idx);}
				if(I->d()!=-1){destinations[I->d()].erase(I->idx);}
                if((I->Type()==(type::ld)||I->Type()==(type::sd))&&I->s1()!=-1){
                    load_stores[I->s1()].erase(I->idx);
                }
				Update_Children(Instructions,sources,destinations,Wait_List,load_stores,I,Executed_Including_NOP,processor);
			}
			else{
				Final_Instructions.push_back(-1);
			}
			// Pushing ready ones from waitlist into prority queue
            std::vector<struct Instruction_Node *> remove;
            if(!Wait_List.empty()){
			for(auto it=Wait_List.begin();it!=Wait_List.end();++it){
				struct Instruction_Node *I=*it;
				if(I->expected_index<=Executed_Including_NOP){
					Priority_List.push(I);
					remove.push_back(I);
				}
			}
            for(auto *I:remove){
                Wait_List.erase(I);
            }
        }
		}
	}
}

}