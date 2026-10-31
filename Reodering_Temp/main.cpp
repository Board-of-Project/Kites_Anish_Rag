#include "scheduler.h"
#include "dependency_graph.h"
#include "translator.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>


// call the main function
void reorder() {
    std::vector<int> finalorder;
    std::vector<std::string> temp;
    Scheduler(finalorder);
    hex_to_array(temp);
    std::vector<std::string> Final;
    std::string NOP="0x00000033";
    for(int i:finalorder){
        if(i>=0){
            Final.push_back(temp[i]);
        }
        else{
            Final.push_back(NOP);
        }
    }
    write_to_file(Final);
}

int main() {
    reorder();
    return 0;
}

