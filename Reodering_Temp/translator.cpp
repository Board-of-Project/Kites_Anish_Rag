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

// reads the instruction from file
void hex_to_array(std::vector<std::string> &S, std::string input_filename){
    std::ifstream hexFile(input_filename);
    if (!hexFile.is_open()) {
        std::cerr << "Error: Could not open the hex file!" << std::endl;
    }

    std::string line;
    int lineCount = 0;
    // Read the file line by line
    while (std::getline(hexFile, line)) {
        lineCount++;

        if (line.empty()) continue;
        S.push_back(line);
    }

    // Always close the stream
    hexFile.close();

}

// hex to text
std::string hex_to_text(uint32_t instr) {
    uint32_t opcode = instr & 0x7F;
    uint32_t rd     = (instr >> 7) & 0x1F;
    uint32_t funct3 = (instr >> 12) & 0x7;
    uint32_t rs1    = (instr >> 15) & 0x1F;
    uint32_t rs2    = (instr >> 20) & 0x1F;
    uint32_t funct7 = (instr >> 25) & 0x7F;

    std::ostringstream asm_out;

    switch (opcode) {
        case 0x33: { // R-type instructions
            std::string name = "";
            if (funct7 == 0x00) {
                if (funct3 == 0x0) name = "add";
                else if (funct3 == 0x7) name = "and";
                else if (funct3 == 0x6) name = "or";
				else if (funct3 == 0x4) name = "xor";
				else if (funct3 == 0x1) name = "sll";
				else if (funct3 == 0x5) name = "srl";
            } else if (funct7 == 0x20) {
                if (funct3 == 0x0) name = "sub";
				else if (funct3 == 0x5) name = "sra";
            }
            
			if (name == "add" && rd == 0 && rs1 == 0 && rd == 0) {
                asm_out << "nop";
			} else if (!name.empty()) {
                asm_out << name << " x" << rd << ", x" << rs1 << ", x" << rs2;
            } else {
                asm_out << "unknown_r_type";
            }
            break;
        }
        case 0x13: { // I-type ALU instructions
            int32_t imm = static_cast<int32_t>(instr) >> 20; // Sign extension
            std::string name = "";
            if (funct3 == 0x0) name = "addi";
            else if (funct3 == 0x7) name = "andi";
            else if (funct3 == 0x6) name = "ori";
			else if (funct3 == 0x4) name = "xori";
			else if (funct3 == 0x1) name = "slli";
			else if (funct3 == 0x5) name = "srli";
			
			if (!name.empty()) {
                asm_out << name << " x" << rd << ", x" << rs1 << ", " << imm;
            } else {
                asm_out << "unknown_i_type";
            }
            break;
        }
        case 0x03: { // I-type Load instructions
            int32_t imm = static_cast<int32_t>(instr) >> 20;
            std::string name = "";
            if (funct3 == 0x2) name = "lw";
            else if (funct3 == 0x1) name = "lh";
            else if (funct3 == 0x0) name = "lb";

            if (!name.empty()) {
                asm_out << name << " x" << rd << ", " << imm << "(x" << rs1 << ")";
            } else {
                asm_out << "unknown_load";
            }
            break;
        }
        case 0x23: { // S-type Store instructions
            int32_t imm = static_cast<int32_t>((funct7 << 5) | rd) << 20;
            imm = imm >> 20; // Sign extension
            std::string name = "";
            if (funct3 == 0x2) name = "sw";
            else if (funct3 == 0x1) name = "sh";
            else if (funct3 == 0x0) name = "sb";

            if (!name.empty()) {
                asm_out << name << " x" << rs2 << ", " << imm << "(x" << rs1 << ")";
            } else {
                asm_out << "unknown_store";
            }
            break;
        }
        case 0x67: { // JALR
            int32_t imm = static_cast<int32_t>(instr) >> 20;
            asm_out << "jalr x" << rd << ", x" << rs1 << ", " << imm;
            break;
        }
        default:
            asm_out << "unknown_opcode (0x" << std::hex << opcode << ")";
            break;
    }

    return asm_out.str();
}

// write back into a text file
int write_to_file(std::vector<std::string> &opcode_strings, std::string output_filename) {
    std::ofstream outfile(output_filename);

    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << output_filename << " for writing.\n";
        return 1;
    }

    std::cout << "Decoding " << opcode_strings.size() << " instructions and writing to " << output_filename << "...\n\n";

    for (const std::string& op_str : opcode_strings) {
        // Convert hex string to 32-bit unsigned integer
        uint32_t instr = std::stoul(op_str, nullptr, 16);

        // Decode instruction into assembly text
        std::string decoded = hex_to_text(instr);

        // Write instruction to text file line by line
        outfile << decoded << "\n";

        // Print progress to console
        std::cout << decoded << "\n";
    }

    outfile.close();
    std::cout << "\nSuccessfully written all decoded instructions to '" << output_filename << "'.\n";

    return 0;
}
