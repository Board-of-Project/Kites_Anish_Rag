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
// Sign-extend the low `bits` bits of `value`
static inline int32_t sext(uint32_t value, int bits) {
    uint32_t m = 1u << (bits - 1);
    return static_cast<int32_t>((value ^ m) - m);
}

std::string hex_to_text(uint32_t instr) {
    uint32_t opcode = instr & 0x7F;
    uint32_t rd     = (instr >> 7)  & 0x1F;
    uint32_t funct3 = (instr >> 12) & 0x7;
    uint32_t rs1    = (instr >> 15) & 0x1F;
    uint32_t rs2    = (instr >> 20) & 0x1F;
    uint32_t funct7 = (instr >> 25) & 0x7F;

    std::ostringstream out;

    switch (opcode) {

    // ---------------- R-type ----------------
    case 0x33: {
        std::string name;
        if (funct7 == 0x00) {
            switch (funct3) {
                case 0x0: name = "add";  break;
                case 0x1: name = "sll";  break;
                case 0x2: name = "slt";  break;
                case 0x3: name = "sltu"; break;
                case 0x4: name = "xor";  break;
                case 0x5: name = "srl";  break;
                case 0x6: name = "or";   break;
                case 0x7: name = "and";  break;
            }
        } else if (funct7 == 0x20) {
            if (funct3 == 0x0) name = "sub";
            else if (funct3 == 0x5) name = "sra";
        } else if (funct7 == 0x01) { // M extension
            switch (funct3) {
                case 0x0: name = "mul";    break;
                case 0x1: name = "mulh";   break;
                case 0x2: name = "mulhsu"; break;
                case 0x3: name = "mulhu";  break;
                case 0x4: name = "div";    break;
                case 0x5: name = "divu";   break;
                case 0x6: name = "rem";    break;
                case 0x7: name = "remu";   break;
            }
        }

        if (!name.empty())
            out << name << " x" << rd << ", x" << rs1 << ", x" << rs2;
        else
            out << "unknown_r_type";
        break;
    }

    // ---------------- I-type ALU ----------------
    case 0x13: {
        int32_t imm = static_cast<int32_t>(instr) >> 20;
        uint32_t shamt = (instr >> 20) & 0x1F;
        std::string name;
        bool is_shift = false;

        switch (funct3) {
            case 0x0: name = "addi";  break;
            case 0x2: name = "slti";  break;
            case 0x3: name = "sltiu"; break;
            case 0x4: name = "xori";  break;
            case 0x6: name = "ori";   break;
            case 0x7: name = "andi";  break;
            case 0x1:
                if (funct7 == 0x00) { name = "slli"; is_shift = true; }
                break;
            case 0x5:
                if (funct7 == 0x00)      { name = "srli"; is_shift = true; }
                else if (funct7 == 0x20) { name = "srai"; is_shift = true; }
                break;
        }

        if (!name.empty())
            out << name << " x" << rd << ", x" << rs1 << ", "
                << (is_shift ? static_cast<int32_t>(shamt) : imm);
        else
            out << "unknown_i_type";
        break;
    }

    // ---------------- Loads ----------------
    case 0x03: {
        int32_t imm = static_cast<int32_t>(instr) >> 20;
        std::string name;
        switch (funct3) {
            case 0x0: name = "lb";  break;
            case 0x1: name = "lh";  break;
            case 0x2: name = "lw";  break;
            case 0x4: name = "lbu"; break;
            case 0x5: name = "lhu"; break;
        }
        if (!name.empty())
            out << name << " x" << rd << ", " << imm << "(x" << rs1 << ")";
        else
            out << "unknown_load";
        break;
    }

    // ---------------- Stores ----------------
    case 0x23: {
        int32_t imm = sext((funct7 << 5) | rd, 12);
        std::string name;
        switch (funct3) {
            case 0x0: name = "sb"; break;
            case 0x1: name = "sh"; break;
            case 0x2: name = "sw"; break;
        }
        if (!name.empty())
            out << name << " x" << rs2 << ", " << imm << "(x" << rs1 << ")";
        else
            out << "unknown_store";
        break;
    }

    // ---------------- Branches (B-type) ----------------
    case 0x63: {
        // imm[12|10:5|4:1|11]
        uint32_t raw = (((instr >> 31) & 0x1)  << 12) |
                       (((instr >> 7)  & 0x1)  << 11) |
                       (((instr >> 25) & 0x3F) << 5)  |
                       (((instr >> 8)  & 0xF)  << 1);
        int32_t imm = sext(raw, 13);
        std::string name;
        switch (funct3) {
            case 0x0: name = "beq";  break;
            case 0x1: name = "bne";  break;
            case 0x4: name = "blt";  break;
            case 0x5: name = "bge";  break;
            case 0x6: name = "bltu"; break;
            case 0x7: name = "bgeu"; break;
        }
        if (!name.empty())
            out << name << " x" << rs1 << ", x" << rs2 << ", " << imm;
        else
            out << "unknown_branch";
        break;
    }

    // ---------------- JAL (J-type) ----------------
    case 0x6F: {
        // imm[20|10:1|11|19:12]
        uint32_t raw = (((instr >> 31) & 0x1)   << 20) |
                       (((instr >> 12) & 0xFF)  << 12) |
                       (((instr >> 20) & 0x1)   << 11) |
                       (((instr >> 21) & 0x3FF) << 1);
        int32_t imm = sext(raw, 21);
        out << "jal x" << rd << ", " << imm;
        break;
    }

    // ---------------- JALR ----------------
    case 0x67: {
        if (funct3 != 0x0) { out << "unknown_jalr"; break; }
        int32_t imm = static_cast<int32_t>(instr) >> 20;
        out << "jalr x" << rd << ", " << imm << "(x" << rs1 << ")";
        break;
    }

    // ---------------- LUI / AUIPC (U-type) ----------------
    case 0x37:
        out << "lui x" << rd << ", 0x" << std::hex << (instr >> 12);
        break;
    case 0x17:
        out << "auipc x" << rd << ", 0x" << std::hex << (instr >> 12);
        break;

    // ---------------- FENCE ----------------
    case 0x0F:
        out << "fence";
        break;

    // ---------------- SYSTEM ----------------
    case 0x73: {
        uint32_t imm12 = instr >> 20;
        if (funct3 == 0x0 && imm12 == 0x0)      out << "ecall";
        else if (funct3 == 0x0 && imm12 == 0x1) out << "ebreak";
        else                                    out << "unknown_system";
        break;
    }

    default:
        out << "unknown_opcode (0x" << std::hex << opcode << ")";
        break;
    }

    return out.str();
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
