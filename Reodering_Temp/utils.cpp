#include "utils.h"
#include <vector>
#include <iostream>

// num of nops in between
int Nops_Needed(struct Instruction_Node * &I1,struct Instruction_Node * &I2){
    if((I1->d==I2->s1||I1->d==I2->s2) && I1->d!=-1){
        return 2;
    }
    return 0;
}

// counts the number of nops to be added
void Num_Hazards(std::vector <std::vector <struct Instruction_Node*>>& Instruction_blocks) {
	// flattening
	std::vector<struct Instruction_Node*> Instructions;
	for (auto& block: Instruction_blocks) {
		Instructions.insert(Instructions.end(), block.begin(), block.end());
	}
	
	int range=2; // the range of influence to check, current set to 2
	int n=Instructions.size();
	int hazards=0;
	std::vector <int> cumm_nops(n,0);
	
	for (int child=1; child<n; child++) {
		cumm_nops[child]=cumm_nops[child-1];
		for (int parent=child-1; parent>=0 && parent>=child-range; parent--) {
			int curr_gap = cumm_nops[child]-cumm_nops[parent] + child-parent-1;
			int ideal_gap = Nops_Needed(Instructions[parent], Instructions[child]);
			cumm_nops[child] = cumm_nops[child] + ((ideal_gap>curr_gap)?(ideal_gap-curr_gap):0);
			if (child-parent-1 < ideal_gap) hazards++;
		}
	}

	std::cout << "This code currently has " << hazards << " data hazards,\n";
	std::cout << "Number of nops to be added without rearrangement " << cumm_nops[cumm_nops.size()-1] << "\n";
	

}