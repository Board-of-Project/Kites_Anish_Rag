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

void hex_to_array(std::vector<std::string> &S, std::string input_filename="instructions.hex");
std::string hex_to_text(uint32_t instr);
int write_to_file(std::vector<std::string> &opcode_strings, std::string output_filename="decoded_instructions.txt");


#endif