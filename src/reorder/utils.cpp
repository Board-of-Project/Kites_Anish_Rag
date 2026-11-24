#include "utils.h"
#include <vector>
#include <iostream>
#include "dependency_graph.h"

//check overlap
bool overlap(int h1,int h2,int l1,int l2){
    return !(l1>=h2||l2>=h1);
}

namespace Kites::reorder{
// num of nops in between
int nopsNeeded(struct Kites::reorder::InstructionNode * &node1,struct Kites::reorder::InstructionNode * &node2,Kites::reorder::Proc p){
	switch(p) {
		case Proc::SingleCycle: {
			return 0;
		}

		case Proc::NoHazardFwd: case Proc::HazardFwd: {
			if ( (node1->type()==(InstructionKind::Ld)) && ((node1->d()==node2->s1()) || (node1->d()==node2->s2())) && node1->d()!=-1 ) {
				return 1;
			}
			else {
				return 0;
			}
		}

		case Proc::HazardNoFwd: case Proc::NoHazardNoFwd: {
			if((node1->d()==node2->s1()||node1->d()==node2->s2()) && node1->d()!=-1){
				return 2;
			}
			else {
				return 0;
			}
		}
	}
}

// counts the number of nops to be added
void numHazards(std::vector <std::vector <struct Kites::reorder::InstructionNode*>>& instructionBlocks,Kites::reorder::Proc p) {
	// flattening
	std::vector<struct Kites::reorder::InstructionNode*> instructions;
	for (auto& block: instructionBlocks) {
		instructions.insert(instructions.end(), block.begin(), block.end());
	}
	
	int range=2; // the range of influence to check, current set to 2
	int n=instructions.size();
	int hazards=0;
	std::vector <int> cummNops(n,0);
	
	for (int child=1; child<n; child++) {
		cummNops[child]=cummNops[child-1];
		for (int parent=child-1; parent>=0 && parent>=child-range; parent--) {
			int currGap = cummNops[child]-cummNops[parent] + child-parent-1;
			int idealGap = nopsNeeded(instructions[parent], instructions[child],p);
			cummNops[child] = cummNops[child] + ((idealGap>currGap)?(idealGap-currGap):0);
			if (child-parent-1 < idealGap) hazards++;
		}
	}

	std::cout << "This code currently has " << hazards << " data hazards,\n";
	std::cout << "Number of nops to be added without rearrangement " << cummNops[cummNops.size()-1] << "\n";
	

}

int edge(struct InstructionNode *node1,struct InstructionNode *node2){
	//waw reg
	if(node1->d()==node2->d()&&node1->d()!=-1){
		return 1;
	}
	//war reg
	else if(node1->s1()==node2->d()&&node1->s1()!=-1){
		return 1;
	}
	else if(node1->s2()==node2->d()&&node1->s2()!=-1){
		return 1;
	}
	//raw reg
	else if((node1->d()==node2->s1()||node1->d()==node2->s2())&&node1->d()!=-1){
		return 1;
	}
	else if(((node2->type()==(InstructionKind::Ld) || node2->type()==(InstructionKind::Sd))&&node1->type()==(InstructionKind::Sd))||(node1->type()==(InstructionKind::Ld)&&node2->type()==(InstructionKind::Sd))){
		if(!(node1->s1()==node2->s1()&&(!overlap(node1->imm()+node1->size(),node2->imm()+node2->size(),node1->imm(),node2->imm()))&&node1->lastTouchedS1==node2->lastTouchedS1)){
			return 1;
		}
	}
	return 0;
}


}