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

namespace Kites::reorder{
//check if free
bool checkDependecy(
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<std::map<int,int> >&loadStores,
    std::vector<struct InstructionNode *>&instructions,
    struct InstructionNode * node
){
    if(node->type()==(InstructionKind::Ld)){
        //WAR in mem
        if(node->s1()!=-1){
        for(const auto & child:loadStores[node->s1()]){
            int index=child.first;
            if(index>=node->idx){
                break;
            }
            if(instructions[index]->type()==(InstructionKind::Sd)){
                struct InstructionNode * node2=instructions[index];
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    return false;
                }
            }
        }
        }
        else{
            for(struct Kites::reorder::InstructionNode *node2:instructions){
                if(node2->idx>=node->idx){break;}
                if(node2->type()==(InstructionKind::Sd)){
                    if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    return false;
                }
                }
            }
        }
    }
    if(node->type()==(InstructionKind::Sd)){
        //WAW in mem
        if(node->s1()!=-1){
        for(const auto & child:loadStores[node->s1()]){
            int index=child.first;
            if(index>=node->idx){
                break;
            }
            if(instructions[index]->type()==(InstructionKind::Sd)){
                struct InstructionNode * node2=instructions[index];
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    return false;
                }
            }
        }
        //RAW in mem
        for(const auto & child:loadStores[node->s1()]){
            int index=child.first;
            if(index>=node->idx){
                break;
            }
            if(instructions[index]->type()==(InstructionKind::Ld)){
                struct InstructionNode * node2=instructions[index];
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    return false;
                }
            }
        }
    }
    else{
        for(struct Kites::reorder::InstructionNode *node2:instructions){
            if(node2->idx>=node->idx){break;}
            if(node2->type()==(InstructionKind::Sd)||node2->type()==(InstructionKind::Ld)){
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                return false;
            }
            }
        }
    }
    }
    int source=node->s1();
    if(source==-1||destinations[source].empty()||destinations[source].begin()->first>=node->idx){
        source=node->s2();
        if(source==-1||destinations[source].empty()||destinations[source].begin()->first>=node->idx){
            int destination=node->d();
            if(destination==-1||sources[destination].empty()||sources[destination].begin()->first>=node->idx){
                if(destination==-1||destinations[destination].empty()||destinations[destination].begin()->first>=node->idx){
                    return true;
            }
            }
        }
    }
    return false;
}

void initialize(std::priority_queue<struct InstructionNode *,std::vector<struct InstructionNode *>,CompareInstructions> &priorityList,
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::vector<std::map<int,int> >&loadStores
){
    for(int i=0;i<instructions.size();i+=1){
        if(Kites::reorder::checkDependecy(sources,destinations,loadStores,instructions,instructions[i])){
            priorityList.push(instructions[i]);
        }
    }
}

// not-ready list to waitlist transfer
void updateChildren(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    std::set<struct InstructionNode *> &waitList,
    std::vector<std::map<int,int>> &loadStores,
    struct InstructionNode *node,
    int executedIncludingNop,
    Kites::reorder::Proc p
){
    //WAR in reg for rs1
    if(node->s1()!=-1 && !destinations[node->s1()].empty()){
        for(const auto & child:destinations[node->s1()]){
            if(child.first>node->idx){
                int expected=executedIncludingNop+nopsNeeded(node,instructions[child.first],p);
                instructions[child.first]->expectedIndex=std::max(expected,instructions[child.first]->expectedIndex);
                if(checkDependecy(sources,destinations,loadStores,instructions,instructions[child.first])){
                    waitList.insert(instructions[child.first]);
                }
            }
        }
    }
    //WAR in reg for rs2
    if(node->s2()!=-1 && !destinations[node->s2()].empty()){
        for(const auto & child:destinations[node->s2()]){
            if(child.first>node->idx){
                int expected=executedIncludingNop+nopsNeeded(node,instructions[child.first],p);
                instructions[child.first]->expectedIndex=std::max(expected,instructions[child.first]->expectedIndex);
                if(checkDependecy(sources,destinations,loadStores,instructions,instructions[child.first])){
                    waitList.insert(instructions[child.first]);
                }
            }
        }
    }
    //RAW in reg
    if(node->d()!=-1 && !sources[node->d()].empty()){
        for(const auto & child:sources[node->d()]){
            if(child.first>node->idx){
                int expected=executedIncludingNop+nopsNeeded(node,instructions[child.first],p);
                instructions[child.first]->expectedIndex=std::max(expected,instructions[child.first]->expectedIndex);
                if(checkDependecy(sources,destinations,loadStores,instructions,instructions[child.first])){
                    waitList.insert(instructions[child.first]);
                }
            }
        }
    }  
    //WAW in reg
    if(node->d()!=-1 && !destinations[node->d()].empty()){
        for(const auto & child:destinations[node->d()]){
            if(child.first>node->idx){
                int expected=executedIncludingNop+nopsNeeded(node,instructions[child.first],p);
                instructions[child.first]->expectedIndex=std::max(expected,instructions[child.first]->expectedIndex);
                if(checkDependecy(sources,destinations,loadStores,instructions,instructions[child.first])){
                    waitList.insert(instructions[child.first]);
                }
            }
        }
    }
    
    //IF load or store checking for mem
    if(node->type()==(InstructionKind::Ld)&&node->s1()!=-1){
        //WAR
        for(const auto & child:loadStores[node->s1()]){
            if(child.first>node->idx&&instructions[child.first]->type()==(InstructionKind::Sd)){
                struct InstructionNode *node2=instructions[child.first];
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    int expected=executedIncludingNop+nopsNeeded(node,node2,p);
                    node2->expectedIndex=std::max(expected,node2->expectedIndex);
                    if(checkDependecy(sources,destinations,loadStores,instructions,node2)){
                        waitList.insert(node2);
                    }
                }
            }
        }
    }

    if(node->type()==(InstructionKind::Sd)&&node->s1()!=-1){
        //WAW
        for(const auto & child:loadStores[node->s1()]){
            if(child.first>node->idx&&instructions[child.first]->type()==(InstructionKind::Sd)){
                struct InstructionNode *node2=instructions[child.first];
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    int expected=executedIncludingNop+nopsNeeded(node,node2,p);
                    node2->expectedIndex=std::max(expected,node2->expectedIndex);
                    if(checkDependecy(sources,destinations,loadStores,instructions,node2)){
                        waitList.insert(node2);
                    }
                }
            }
        }
        //RAW
        for(const auto & child:loadStores[node->s1()]){
            if(child.first>node->idx&&instructions[child.first]->type()==(InstructionKind::Ld)){
                struct InstructionNode *node2=instructions[child.first];
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    int expected=executedIncludingNop+nopsNeeded(node,node2,p);
                    node2->expectedIndex=std::max(expected,node2->expectedIndex);
                    if(checkDependecy(sources,destinations,loadStores,instructions,node2)){
                        waitList.insert(node2);
                    }
                }
            }
        }
    }
    //waw or raw x0
    if((node->type()==(InstructionKind::Sd))&&node->s1()==-1){
        for(struct Kites::reorder::InstructionNode *node2: instructions){
            if(node2->idx>node->idx&&(node2->type()==(InstructionKind::Sd)||node2->type()==(InstructionKind::Ld))){
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    int expected=executedIncludingNop+nopsNeeded(node,node2,p);
                    node2->expectedIndex=std::max(expected,node2->expectedIndex);
                    if(checkDependecy(sources,destinations,loadStores,instructions,node2)){
                        waitList.insert(node2);
                    }
                }
            }
        }
    }
    //war x0
    if((node->type()==(InstructionKind::Ld))&&node->s1()==-1){
        for(struct Kites::reorder::InstructionNode *node2: instructions){
            if(node2->idx>node->idx&&node2->type()==(InstructionKind::Sd)){
                if(!(node->s1()==node2->s1()&&(!overlap(node->imm()+node->size(),node2->imm()+node2->size(),node->imm(),node2->imm()))&&node->lastTouchedS1==node2->lastTouchedS1)){
                    int expected=executedIncludingNop+nopsNeeded(node,node2,p);
                    node2->expectedIndex=std::max(expected,node2->expectedIndex);
                    if(checkDependecy(sources,destinations,loadStores,instructions,node2)){
                        waitList.insert(node2);
                    }
                }
            }
        }
    }
}

// schedules the instructions and stores in the array passed
void scheduler(std::vector<int>&finalInstructions, const std::vector<uint32_t>&hexcodes,Kites::reorder::Proc processor,std::vector<Kites::reorder::HeuristicEntry> heuristics) {
    // std::vector<struct InstructionNode *> instructions;
    // readFile(instructions);
	std::vector <std::vector <struct InstructionNode*>> instructionBlocks;
	readFileForBranch(instructionBlocks,hexcodes);
	// prints the number of hazards
	numHazards(instructionBlocks,processor);
	int executedIncludingNop=0;
	for (std::vector <struct InstructionNode*> instructions: instructionBlocks) {
		if(instructions.size()==0){
            continue;
        }
		// check if the first instruction is branch
		if (instructions[0]->branchFlag) {
			finalInstructions.push_back(instructions[0]->idx);
			instructions.erase(instructions.begin());
		}
		if(instructions.size()==0){
            continue;
        }
        int index1=instructions[0]->idx;
        std::vector<int> lastTouched(32,-1);
        for(struct InstructionNode * node:instructions){
            node->idx=node->idx-index1;
            if(node->d()>=0){lastTouched[node->d()]=node->idx;}
            if(node->s1()>=0){node->lastTouchedS1=lastTouched[node->s1()];}
        }
		std::vector<std::map<int,int>> sources(32);
		std::vector<std::map<int,int>> destinations(32);
        std::vector<std::map<int,int>>loadStores(32);
		makeGraph(instructions,sources,destinations,loadStores);

		//Heuristic of choice
        for(HeuristicEntry entry : heuristics){
    	entry.fn(instructions,sources,destinations,processor);}

		std::priority_queue<struct InstructionNode *,std::vector<struct InstructionNode *>,CompareInstructions> priorityList;
		std::set<struct InstructionNode *> waitList;
		initialize(priorityList,instructions,sources,destinations,loadStores);
		int executed=0;
		int n=instructions.size();
		while(executed<n){
			executedIncludingNop+=1;
			if(!priorityList.empty()){
				executed+=1;
				struct InstructionNode * node=priorityList.top();
				finalInstructions.push_back(node->idx+index1);
				priorityList.pop(); // pluck an instruction
				std::cout<<"Executed "<<node->idx+index1+1<<"\n";
				if(node->s1()!=-1){sources[node->s1()].erase(node->idx);}
				if(node->s2()!=-1){sources[node->s2()].erase(node->idx);}
				if(node->d()!=-1){destinations[node->d()].erase(node->idx);}
                if((node->type()==(InstructionKind::Ld)||node->type()==(InstructionKind::Sd))&&node->s1()!=-1){
                    loadStores[node->s1()].erase(node->idx);
                }
				updateChildren(instructions,sources,destinations,waitList,loadStores,node,executedIncludingNop,processor);
			}
			else{
				finalInstructions.push_back(-1);
			}
			// Pushing ready ones from waitlist into prority queue
            std::vector<struct InstructionNode *> remove;
            if(!waitList.empty()){
			for(auto it=waitList.begin();it!=waitList.end();++it){
				struct InstructionNode *node=*it;
				if(node->expectedIndex<=executedIncludingNop){
					priorityList.push(node);
					remove.push_back(node);
				}
			}
            for(auto *node:remove){
                waitList.erase(node);
            }
        }
		}
	}
}

}