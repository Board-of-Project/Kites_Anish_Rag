#include "dependency_graph.h"
#include "heuristic.h"
#include "utils.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>

int subtree(
    std::vector<int> &dependencies,
    std::vector<struct Kites::reorder::InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    int index,
    Kites::reorder::Proc processor
){
    if(dependencies[index]!=-1){return dependencies[index];}
    else{
        int ans=0;
        for(int i=index+1;i<instructions.size();i+=1){
            //waw reg
            if(instructions[i]->d()==instructions[index]->d()&&instructions[index]->d()!=-1){
                ans+=subtree(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1;
            }
            //war reg
            else if(instructions[index]->s1()==instructions[i]->d()&&instructions[index]->s1()!=-1){
                ans+=subtree(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1;
            }
            else if(instructions[index]->s2()==instructions[i]->d()&&instructions[index]->s2()!=-1){
                ans+=subtree(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1;
            }
            //raw reg
            else if((instructions[index]->d()==instructions[i]->s1()||instructions[index]->d()==instructions[i]->s2())&&instructions[index]->d()!=-1){
                ans+=subtree(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1;
            }
            else if(((instructions[i]->type()==(InstructionKind::Ld) || instructions[i]->type()==(InstructionKind::Sd))&&instructions[index]->type()==(InstructionKind::Sd))||(instructions[index]->type()==(InstructionKind::Ld)&&instructions[i]->type()==(InstructionKind::Sd))){
                if(!(instructions[index]->s1()==instructions[i]->s1()&&(!overlap(instructions[index]->imm()+instructions[index]->size(),instructions[i]->imm()+instructions[i]->size(),instructions[index]->imm(),instructions[i]->imm()))&&instructions[index]->lastTouchedS1==instructions[i]->lastTouchedS1)){
                    ans+=subtree(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1;
                }
	        }
        }
        dependencies[index]=ans;
        return ans;
    }
}

int deep(
    std::vector<int> &dependencies,
    std::vector<struct Kites::reorder::InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    int index,
    Kites::reorder::Proc processor
){
    if(dependencies[index]!=-1){return dependencies[index];}
    else{
        int ans=0;
        for(int i=index+1;i<instructions.size();i+=1){
            //waw reg
            if(instructions[i]->d()==instructions[index]->d()&&instructions[index]->d()!=-1){
                ans=std::max(ans,deep(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1);
            }
            //war reg
            else if(instructions[index]->s1()==instructions[i]->d()&&instructions[index]->s1()!=-1){
                ans=std::max(ans,deep(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1);
            }
            else if(instructions[index]->s2()==instructions[i]->d()&&instructions[index]->s2()!=-1){
                ans=std::max(ans,deep(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1);
            }
            //raw reg
            else if((instructions[index]->d()==instructions[i]->s1()||instructions[index]->d()==instructions[i]->s2())&&instructions[index]->d()!=-1){
                ans=std::max(ans,deep(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1);
            }
            else if(((instructions[i]->type()==(InstructionKind::Ld) || instructions[i]->type()==(InstructionKind::Sd))&&instructions[index]->type()==(InstructionKind::Sd))||(instructions[index]->type()==(InstructionKind::Ld)&&instructions[i]->type()==(InstructionKind::Sd))){
                if(!(instructions[index]->s1()==instructions[i]->s1()&&(!overlap(instructions[index]->imm()+instructions[index]->size(),instructions[i]->imm()+instructions[i]->size(),instructions[index]->imm(),instructions[i]->imm()))&&instructions[index]->lastTouchedS1==instructions[i]->lastTouchedS1)){
                    ans=std::max(ans,deep(dependencies,instructions,sources,destinations,i,processor)+Kites::reorder::nopsNeeded(instructions[index],instructions[i],processor)+1);
                }
	        }
        }
        dependencies[index]=ans;
        return ans;
    }
}

void mlData(
    std::vector<struct Kites::reorder::InstructionNode *> instructions,
    std::vector<std::vector<int>> &adj,
    std::vector<std::vector<int>> &me,
    Kites::reorder::Proc p
){
    for(int i=0;i<instructions.size();i+=1){
        me[i][0]=instructions[i]->s1();
        me[i][1]=instructions[i]->s2();
        me[i][2]=instructions[i]->d();
        me[i][3]=0;
        for(int j=i+1;j<instructions.size();j+=1){
            if(Kites::reorder::edge(instructions[i],instructions[j])){
                adj[i][j]=Kites::reorder::nopsNeeded(instructions[i],instructions[j],p)+1;
                me[i][3]+=1;
            }
        }
    }
}

namespace Kites::reorder {

// 1. Implementation of heuristic1
void heuristic1(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
) {
    int n = instructions.size();
    std::vector<int> dependecies(n, -1);
    for(int i = 0; i < instructions.size(); i += 1) {
        // Explicit qualification if Subtree is outside the namespace
        instructions[i]->priority.push_back((double)(::subtree(dependecies, instructions, sources, destinations, i, p)));
    }
}

// 2. Implementation of heuristic2
void heuristic2(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
) {
    int n = instructions.size();
    for(int i = 0; i < instructions.size(); i += 1) {
        instructions[i]->priority.push_back((double)( n - (instructions[i]->idx)));
    }
}

void heuristicRl1(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    std::vector<std::vector<int>> adj(instructions.size(),std::vector<int>(instructions.size(),0));
    std::vector<std::vector<int>> me(instructions.size(),std::vector<int>(4,0));
    ::mlData(instructions,adj,me,p);

	std::filesystem::create_directory("/tmp/ml");
    std::ofstream out("/tmp/ml/input_adj.bin",std::ios::binary);
    int n=instructions.size();
    out.write(reinterpret_cast<const char*>(&n),sizeof(int));
    for(int i=0;i<instructions.size();i+=1){
        out.write(reinterpret_cast<const char*>(adj[i].data()),adj[i].size()*sizeof(int));
    }

    out.close();


    std::ofstream out2("/tmp/ml/input_me.bin",std::ios::binary);
    for(int i=0;i<instructions.size();i+=1){
        out2.write(reinterpret_cast<const char*>(me[i].data()),me[i].size()*sizeof(int));
    }

    out2.close();

    for(int i=0;i<instructions.size();i+=1){
        instructions[i]->priority.push_back(0.0L);
    }
}


void heuristicRl2(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    std::ifstream in("./ml/priority_out.bin",std::ios::binary);
    std::filesystem::path cur=".";
    //std::cout<<cur.filename().string()<<"\n";
    if(in.is_open()){
        std::vector<double> priotities(instructions.size());
        in.read(reinterpret_cast<char *>(priotities.data()),instructions.size()*sizeof(double));
        in.close();
        for(int i=0;i<instructions.size();i+=1){
            instructions[i]->priority.push_back(priotities[i]);
        }
    }
    else{std::cerr<<"OUtput of model not found\n";}
}

void heuristicRl(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    std::vector<std::vector<int>> adj(instructions.size(),std::vector<int>(instructions.size(),0));
    std::vector<std::vector<int>> me(instructions.size(),std::vector<int>(4,0));
    ::mlData(instructions,adj,me,p);
	std::filesystem::create_directory("/tmp/rl_run");
    std::ofstream out("/tmp/rl_run/input_adj.bin",std::ios::binary);
    int n=instructions.size();
    out.write(reinterpret_cast<const char*>(&n),sizeof(int));
    for(int i=0;i<instructions.size();i+=1){
        out.write(reinterpret_cast<const char*>(adj[i].data()),adj[i].size()*sizeof(int));
    }

    out.close();


    std::ofstream out2("/tmp/rl_run/input_me.bin",std::ios::binary);
    for(int i=0;i<instructions.size();i+=1){
        out2.write(reinterpret_cast<const char*>(me[i].data()),me[i].size()*sizeof(int));
    }

    out2.close();

	int rlStatus=std::system("python3 ./src/reorder/rl_heuristic.py");

	if(rlStatus){
		std::cerr<<"RL model error\n";
	}

	std::ifstream in("/tmp/rl_run/priority_out.bin",std::ios::binary);

    if(in.is_open()){
        std::vector<double> priotities(instructions.size());
        in.read(reinterpret_cast<char *>(priotities.data()),instructions.size()*sizeof(double));
        in.close();
        for(int i=0;i<instructions.size();i+=1){
            instructions[i]->priority.push_back(priotities[i]);
        }
    }
    else{std::cerr<<"OUtput of model not found\n";}
}

void heuristicNull(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    for(struct InstructionNode * node:instructions){
        node->priority.push_back(0.0L);
    }
}

void heuristicChildren(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    for(int index=0;index<instructions.size();index++){
        int ans=0;
        for(int i=index+1;i<instructions.size();i+=1){
            //waw reg
            if(instructions[i]->d()==instructions[index]->d()&&instructions[index]->d()!=-1){
                ans+=Kites::reorder::nopsNeeded(instructions[index],instructions[i],p)+1;
            }
            //war reg
            else if(instructions[index]->s1()==instructions[i]->d()&&instructions[index]->s1()!=-1){
                ans+=Kites::reorder::nopsNeeded(instructions[index],instructions[i],p)+1;
            }
            else if(instructions[index]->s2()==instructions[i]->d()&&instructions[index]->s2()!=-1){
                ans+=Kites::reorder::nopsNeeded(instructions[index],instructions[i],p)+1;
            }
            //raw reg
            else if((instructions[index]->d()==instructions[i]->s1()||instructions[index]->d()==instructions[i]->s2())&&instructions[index]->d()!=-1){
                ans+=Kites::reorder::nopsNeeded(instructions[index],instructions[i],p)+1;
            }
            else if(((instructions[i]->type()==(InstructionKind::Ld) || instructions[i]->type()==(InstructionKind::Sd))&&instructions[index]->type()==(InstructionKind::Sd))||(instructions[index]->type()==(InstructionKind::Ld)&&instructions[i]->type()==(InstructionKind::Sd))){
                if(!(instructions[index]->s1()==instructions[i]->s1()&&(!overlap(instructions[index]->imm()+instructions[index]->size(),instructions[i]->imm()+instructions[i]->size(),instructions[index]->imm(),instructions[i]->imm()))&&instructions[index]->lastTouchedS1==instructions[i]->lastTouchedS1)){
                    ans+=Kites::reorder::nopsNeeded(instructions[index],instructions[i],p)+1;
                }
	        }
        }
        instructions[index]->priority.push_back((double)ans);
    }
}

void heuristicDeep(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    int n = instructions.size();
    std::vector<int> dependecies(n, -1);
    for(int i = 0; i < instructions.size(); i += 1) {
        // Explicit qualification if Subtree is outside the namespace
        instructions[i]->priority.push_back((double)(::deep(dependecies, instructions, sources, destinations, i, p)));
    }
}

} // na
