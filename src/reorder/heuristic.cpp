#include "dependency_graph.h"
#include "heuristic.h"
#include "utils.h"
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>

int Subtree(
    std::vector<int> &Dependencies,
    std::vector<struct Kites::Reorder::Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    int index,
    Kites::Reorder::Proc processor
){
    if(Dependencies[index]!=-1){return Dependencies[index];}
    else{
        int ans=0;
        for(int i=index+1;i<Instructions.size();i+=1){
            //waw reg
            if(Instructions[i]->d()==Instructions[index]->d()&&Instructions[index]->d()!=-1){
                ans+=Subtree(Dependencies,Instructions,sources,destinations,i,processor)+Kites::Reorder::Nops_Needed(Instructions[index],Instructions[i],processor);
            }
            //war reg
            else if(Instructions[index]->s1()==Instructions[i]->d()&&Instructions[index]->s1()!=-1){
                ans+=Subtree(Dependencies,Instructions,sources,destinations,i,processor)+Kites::Reorder::Nops_Needed(Instructions[index],Instructions[i],processor);
            }
            else if(Instructions[index]->s2()==Instructions[i]->d()&&Instructions[index]->s2()!=-1){
                ans+=Subtree(Dependencies,Instructions,sources,destinations,i,processor)+Kites::Reorder::Nops_Needed(Instructions[index],Instructions[i],processor);
            }
            //raw reg
            else if((Instructions[index]->d()==Instructions[i]->s1()||Instructions[index]->d()==Instructions[i]->s2())&&Instructions[index]->d()!=-1){
                ans+=Subtree(Dependencies,Instructions,sources,destinations,i,processor)+Kites::Reorder::Nops_Needed(Instructions[index],Instructions[i],processor);
            }
            else if(((Instructions[i]->Type()==(type::ld) || Instructions[i]->Type()==(type::sd))&&Instructions[index]->Type()==(type::sd))||(Instructions[index]->Type()==(type::ld)&&Instructions[i]->Type()==(type::sd))){
                if(!(Instructions[index]->s1()==Instructions[i]->s1()&&(!overlap(Instructions[index]->imm()+Instructions[index]->size(),Instructions[i]->imm()+Instructions[i]->size(),Instructions[index]->imm(),Instructions[i]->imm()))&&Instructions[index]->last_touched_s1==Instructions[i]->last_touched_s1)){
                    ans+=Subtree(Dependencies,Instructions,sources,destinations,i,processor)+Kites::Reorder::Nops_Needed(Instructions[index],Instructions[i],processor);
                }
	        }
        }
        Dependencies[index]=ans;
        return ans;
    }
}

void Ml_Data(
    std::vector<struct Kites::Reorder::Instruction_Node *> Instructions,
    std::vector<std::vector<int>> &adj,
    std::vector<std::vector<int>> &me,
    Kites::Reorder::Proc p
){
    for(int i=0;i<Instructions.size();i+=1){
        me[i][0]=(int)(Instructions[i]->Type());
        me[i][1]=Instructions[i]->s1();
        me[i][2]=Instructions[i]->s2();
        me[i][3]=Instructions[i]->d();
        me[i][4]=Instructions[i]->idx / Instructions.size();
        for(int j=i+1;j<Instructions.size();j+=1){
            if(Kites::Reorder::Edge(Instructions[i],Instructions[j])){
                adj[i][j]=Kites::Reorder::Nops_Needed(Instructions[i],Instructions[j],p)+1;
            }
        }
    }
}

namespace Kites::Reorder {

// 1. Implementation of Heuristic1
void Heuristic1(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
) {
    int n = Instructions.size();
    std::vector<int> Dependecies(n, -1);
    for(int i = 0; i < Instructions.size(); i += 1) {
        // Explicit qualification if Subtree is outside the namespace
        Instructions[i]->priority.push_back((double)(::Subtree(Dependecies, Instructions, sources, destinations, i, p)));
    }
}

// 2. Implementation of Heuristic2
void Heuristic2(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
) {
    int n = Instructions.size();
    for(int i = 0; i < Instructions.size(); i += 1) {
        Instructions[i]->priority.push_back((double)( n - (Instructions[i]->idx)));
    }
}

void HeuristicRL1(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    std::vector<std::vector<int>> adj(Instructions.size(),std::vector<int>(Instructions.size(),0));
    std::vector<std::vector<int>> me(Instructions.size(),std::vector<int>(5,0));
    ::Ml_Data(Instructions,adj,me,p);

	std::filesystem::create_directory("/tmp/ml");
    std::ofstream out("/tmp/ml/input_adj.bin",std::ios::binary);
    int n=Instructions.size();
    out.write(reinterpret_cast<const char*>(&n),sizeof(int));
    for(int i=0;i<Instructions.size();i+=1){
        out.write(reinterpret_cast<const char*>(adj[i].data()),adj[i].size()*sizeof(int));
    }

    out.close();


    std::ofstream out2("/tmp/ml/input_me.bin",std::ios::binary);
    for(int i=0;i<Instructions.size();i+=1){
        out2.write(reinterpret_cast<const char*>(me[i].data()),me[i].size()*sizeof(int));
    }

    out2.close();

    for(int i=0;i<Instructions.size();i+=1){
        Instructions[i]->priority.push_back(0.0L);
    }
}


void HeuristicRL2(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    std::ifstream in("/tmp/ml/priority_out.bin",std::ios::binary);

    if(in.is_open()){
        std::vector<double> priotities(Instructions.size());
        in.read(reinterpret_cast<char *>(priotities.data()),Instructions.size()*sizeof(double));
        in.close();
        for(int i=0;i<Instructions.size();i+=1){
            Instructions[i]->priority.push_back(priotities[i]);
        }
    }
    else{std::cerr<<"OUtput of model not found\n";}
}

void HeuristicRL(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    std::vector<std::vector<int>> adj(Instructions.size(),std::vector<int>(Instructions.size(),0));
    std::vector<std::vector<int>> me(Instructions.size(),std::vector<int>(5,0));
    ::Ml_Data(Instructions,adj,me,p);
	std::filesystem::create_directory("/tmp/rl_run");
    std::ofstream out("/tmp/rl_run/input_adj.bin",std::ios::binary);
    int n=Instructions.size();
    out.write(reinterpret_cast<const char*>(&n),sizeof(int));
    for(int i=0;i<Instructions.size();i+=1){
        out.write(reinterpret_cast<const char*>(adj[i].data()),adj[i].size()*sizeof(int));
    }

    out.close();


    std::ofstream out2("/tmp/rl_run/input_me.bin",std::ios::binary);
    for(int i=0;i<Instructions.size();i+=1){
        out2.write(reinterpret_cast<const char*>(me[i].data()),me[i].size()*sizeof(int));
    }

    out2.close();

	int RL_status=std::system("python3 ./src/reorder/rl_heuristic.py");

	if(RL_status){
		std::cerr<<"RL model error\n";
	}

	std::ifstream in("/tmp/rl_run/priority_out.bin",std::ios::binary);

    if(in.is_open()){
        std::vector<double> priotities(Instructions.size());
        in.read(reinterpret_cast<char *>(priotities.data()),Instructions.size()*sizeof(double));
        in.close();
        for(int i=0;i<Instructions.size();i+=1){
            Instructions[i]->priority.push_back(priotities[i]);
        }
    }
    else{std::cerr<<"OUtput of model not found\n";}
}

void HeuristicNull(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
){
    for(struct Instruction_Node * I:Instructions){
        I->priority.push_back(0.0L);
    }
}

} // na
