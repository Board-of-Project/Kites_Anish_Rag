#include "dependency_graph.h"
#include "heuristic.h"
#include <vector>
#include <map>
#include <algorithm>

int Subtree(
    std::vector<int> &Dependencies,
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    int index
){
    if(Dependencies[index]!=-1){return Dependencies[index];}
    else{
        if(Instructions[index]->d!=-1&&!sources[Instructions[index]->d].empty()){
            int ans=1;
            for (auto it = sources[Instructions[index]->d].rbegin(); it !=sources[Instructions[index]->d].rend(); ++it) {
                if(it->first<=index){Dependencies[index]=ans;return ans;}
                ans+=Subtree(Dependencies,Instructions,sources,destinations,it->first);
            }
            Dependencies[index]=ans;
            return ans;
        }
        else{
            Dependencies[index]=1;
            return 1;
        }
    }
}

void Heuristic1(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations
){
    int n=Instructions.size();
    std::vector<int> Dependecies(n,-1);
    for(int i=0;i<Instructions.size();i+=1){
        Instructions[i]->priority=Subtree(Dependecies,Instructions,sources,destinations,i);
    }
}

void Heuristic2(
    std::vector<struct Instruction_Node *> &Instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations
){
    int n=Instructions.size();
    for(int i=0;i<Instructions.size();i+=1){
        Instructions[i]->priority=n-(Instructions[i]->idx);
    }
}