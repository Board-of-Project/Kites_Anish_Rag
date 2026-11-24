#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "scheduler.h"
#include "dependency_graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>

void hexToArray(std::vector<std::string> &hexLines, std::string inputFilename="instructions.hex");
std::string hexToText(uint32_t instr);
int writeToFile(std::vector<std::string> &opcodeStrings, std::string outputFilename="/tmp/comp_arch/tests/code2.s");


#endif
