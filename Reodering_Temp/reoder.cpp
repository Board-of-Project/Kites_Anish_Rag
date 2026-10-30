#include "ListScheduler.h"
#include "graphmaker.h"
#include "reoder.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>

void Reader(std::vector<std::string> &S){
    std::ifstream hexFile("instructions.hex");
    if (!hexFile.is_open()) {
        std::cerr << "Error: Could not open the hex file!" << std::endl;
    }

    std::string line;
    int lineCount = 0;
    // 2. Read the file line by line
    while (std::getline(hexFile, line)) {
        lineCount++;

        if (line.empty()) continue;
        S.push_back(line);
    }

    // 4. Always close the stream
    hexFile.close();

}

std::string decode_riscv_instruction(uint32_t instr) {
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
            } else if (funct7 == 0x20) {
                if (funct3 == 0x0) name = "sub";
            }
            
            if (!name.empty()) {
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

            if (name == "addi" && rd == 0 && rs1 == 0 && imm == 0) {
                asm_out << "nop";
            } else if (!name.empty()) {
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

int Writer(std::vector<std::string> &opcode_strings) {
    std::string output_filename = "decoded_instructions.txt";
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
        std::string decoded = decode_riscv_instruction(instr);

        // Write instruction to text file line by line
        outfile << decoded << "\n";

        // Print progress to console
        std::cout << "Hex: " << op_str << " -> Assembly: " << decoded << "\n";
    }

    outfile.close();
    std::cout << "\nSuccessfully written all decoded instructions to '" << output_filename << "'.\n";

    return 0;
}

void Reoderer(){
    std::vector<int> finalorder;
    std::vector<std::string> temp;
    Scheduler(finalorder);
    Reader(temp);
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
    Writer(Final);
}