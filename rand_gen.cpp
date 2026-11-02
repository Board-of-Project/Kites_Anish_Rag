// Random RISC-V program generator for Kites differential testing.
//
//   usage: rand_gen <output.s> [seed] [num_instructions]
//
// Same seed + length => identical program (so a failing case can be reproduced).
//
// Every generated program is guaranteed to terminate and to be "safe" for the VM:
//   * straight-line code plus FORWARD-only branches (no loops, no infinite run)
//   * loads/stores only touch a 256-byte window at BASE_ADDR, always naturally aligned
//   * no stdin reads (the CLI hangs on a READ syscall)
//   * ends by printing a few registers and exiting through ecall
//
// Register roles:
//   s11 (x27)        fixed memory base pointer, never written after setup
//   a0, a7           reserved for the ecall epilogue
//   everything else  random pool (x0 is only ever used as a source)
//
// Instruction set used: RV64I-style ALU/imm ops, M extension (mul/div/rem), loads/stores,
// forward branches. Edit the tables below to widen or narrow coverage.
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace
{
constexpr int BASE_ADDR = 1024; // plain low memory, like the examples/ programs
constexpr int WINDOW = 256;     // bytes addressable above BASE_ADDR

const char *BASE_REG = "s11";

const std::vector<std::string> POOL = {
    "t0", "t1", "t2", "s0", "s1", "a1", "a2", "a3", "a4", "a5", "a6",
    "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "t3", "t4", "t5", "t6"};

const std::vector<std::string> R_OPS = {"add", "sub", "and", "or",  "xor",  "sll",  "srl",
                                        "sra", "slt", "sltu"};
const std::vector<std::string> I_OPS = {"addi", "andi", "ori", "xori", "slti", "sltiu"};
const std::vector<std::string> SHIFT_I_OPS = {"slli", "srli", "srai"};
const std::vector<std::string> BRANCH_OPS = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};

struct MemOp
{
    const char *name;
    int size; // bytes, also the required alignment
    bool store;
};
const std::vector<MemOp> MEM_OPS = {
    {"lb", 1, false}, {"lbu", 1, false}, {"lh", 2, false}, {"lhu", 2, false},
    {"lw", 4, false}, {"lwu", 4, false}, {"ld", 8, false}, {"sb", 1, true},
    {"sh", 2, true},  {"sw", 4, true},   {"sd", 8, true},
};

std::mt19937_64 rng;

int rnd(int lo, int hi) { return std::uniform_int_distribution<int>(lo, hi)(rng); }

template <typename T>
const T &pick(const std::vector<T> &v)
{
    return v[rnd(0, static_cast<int>(v.size()) - 1)];
}

// Sources may be x0; destinations never are.
std::string srcReg() { return rnd(0, 11) == 0 ? "zero" : pick(POOL); }
std::string dstReg() { return pick(POOL); }

// Mostly small values, sometimes edge cases that stress div/rem/shift/sign handling.
int64_t interestingValue()
{
    switch (rnd(0, 9))
    {
    case 0: return 0;
    case 1: return 1;
    case 2: return -1;
    case 3: return INT32_MAX;
    case 4: return INT32_MIN;
    case 5: return rnd(-2048, 2047);
    default: return static_cast<int64_t>(rnd(-1000000, 1000000)) * rnd(1, 2000);
    }
}

struct PendingLabel
{
    int dueAtInstr;
    std::string name;
};
} // namespace

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <output.s> [seed] [num_instructions]\n";
        return 1;
    }
    const std::string outPath = argv[1];
    const uint64_t seed = argc > 2 ? std::strtoull(argv[2], nullptr, 10) : std::random_device{}();
    const int length = argc > 3 ? std::atoi(argv[3]) : 60;
    if (length < 1)
    {
        std::cerr << "num_instructions must be >= 1\n";
        return 1;
    }
    rng.seed(seed);

    std::ofstream out(outPath);
    if (!out)
    {
        std::cerr << "cannot open " << outPath << " for writing\n";
        return 1;
    }

    out << "# rand_gen seed=" << seed << " length=" << length << "\n";
    out << "li " << BASE_REG << ", " << BASE_ADDR << "\n";
    for (const auto &r : POOL)
        out << "li " << r << ", " << interestingValue() << "\n";

    std::vector<PendingLabel> pending;
    int labelCounter = 0;

    for (int i = 0; i < length; ++i)
    {
        // Place any forward-branch targets that are due here.
        for (auto it = pending.begin(); it != pending.end();)
        {
            if (it->dueAtInstr <= i)
            {
                out << it->name << ":\n";
                it = pending.erase(it);
            }
            else
                ++it;
        }

        const int kind = rnd(0, 99);
        if (kind < 38)
        {
            out << pick(R_OPS) << " " << dstReg() << ", " << srcReg() << ", " << srcReg() << "\n";
        }
        else if (kind < 55)
        {
            out << pick(I_OPS) << " " << dstReg() << ", " << srcReg() << ", " << rnd(-2048, 2047)
                << "\n";
        }
        else if (kind < 63)
        {
            out << pick(SHIFT_I_OPS) << " " << dstReg() << ", " << srcReg() << ", " << rnd(0, 31)
                << "\n";
        }
        else if (kind < 68)
        {
            out << "li " << dstReg() << ", " << interestingValue() << "\n";
        }
        else if (kind < 72)
        {
            out << "mv " << dstReg() << ", " << srcReg() << "\n";
        }
        else if (kind < 88)
        {
            const MemOp &m = pick(MEM_OPS);
            const int offset = rnd(0, WINDOW / m.size - 1) * m.size; // aligned, inside window
            out << m.name << " " << (m.store ? srcReg() : dstReg()) << ", " << offset << "("
                << BASE_REG << ")\n";
        }
        else
        {
            // Forward branch over the next 1..4 instructions.
            std::string label = "L" + std::to_string(labelCounter++);
            out << pick(BRANCH_OPS) << " " << srcReg() << ", " << srcReg() << ", " << label << "\n";
            pending.push_back({i + 1 + rnd(1, 4), label});
        }
    }

    // Any label still pending goes right before the epilogue so every branch resolves.
    for (const auto &p : pending)
        out << p.name << ":\n";

    // Epilogue: print a handful of registers, then exit(0).
    for (int k = 0; k < 6; ++k)
    {
        out << "mv a0, " << POOL[rnd(0, static_cast<int>(POOL.size()) - 1)] << "\n";
        out << "li a7, 1\n";
        out << "ecall\n";
    }
    out << "li a0, 0\n";
    out << "li a7, 10\n";
    out << "ecall\n";

    return out ? 0 : 1;
}
