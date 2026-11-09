#include "dependency_graph.h"
#include "heuristic.h"
#include "utils.h"
#include <vector>
#include <map>
#include <algorithm>

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
            else if((Instructions[i]->Type()==(type::ld)||Instructions[i]->Type()==(type::sd))&&(Instructions[index]->Type()==(type::ld)||Instructions[index]->Type()==(type::sd))){
                if(!(Instructions[index]->s1()==Instructions[i]->s1()&&(!overlap(Instructions[index]->imm()+Instructions[index]->size(),Instructions[i]->imm()+Instructions[i]->size(),Instructions[index]->imm(),Instructions[i]->imm()))&&Instructions[index]->last_touched_s1==Instructions[i]->last_touched_s1)){
                    ans+=Subtree(Dependencies,Instructions,sources,destinations,i,processor)+Kites::Reorder::Nops_Needed(Instructions[index],Instructions[i],processor);
                }
	        }
        }
        Dependencies[index]=ans;
        return ans;
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
        Instructions[i]->priority = ::Subtree(Dependecies, Instructions, sources, destinations, i, p);
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
        Instructions[i]->priority = n - (Instructions[i]->idx);
    }
}

} // na