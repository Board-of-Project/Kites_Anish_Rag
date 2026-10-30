#ifndef REODER_H
#define REODER_H

#include "ListScheduler.h"
#include "graphmaker.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>

void Reader(std::vector<std::string> &S);
void Reoderer();
std::string decode_riscv_instruction(uint32_t instr);
int Writer(std::vector<std::string> &opcode_strings);


#endif