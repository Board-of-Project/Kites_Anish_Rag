#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "dependency_graph.h"
#include "utils.h"
#include <vector>
#include <map>

namespace Kites::reorder{

using HeuristicFn =void (*)(
    std::vector<struct Kites::reorder::InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Proc p
);

struct HeuristicEntry
{
    const char *name;  // shown in the dropdown
    HeuristicFn fn;
};
void heuristic1(
    std::vector<struct Kites::reorder::InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Proc p
);
void heuristic2(
    std::vector<struct Kites::reorder::InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Proc p
);
void heuristicRl1(
    std::vector<struct Kites::reorder::InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Proc p
);
void heuristicRl2(
    std::vector<struct Kites::reorder::InstructionNode *> &instructions,
    std::vector<std::map<int,int> >&sources,
    std::vector<std::map<int,int> >&destinations,
    Proc p
);
void heuristicRl(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
);
void heuristicNull(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
);
void heuristicChildren(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
);
void heuristicDeep(
    std::vector<struct InstructionNode *> &instructions,
    std::vector<std::map<int,int> > &sources,
    std::vector<std::map<int,int> > &destinations,
    Proc p
);
}
#endif