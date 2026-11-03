// Random RISC-V program generator for Kites differential testing (short-program version, no ecall).
//
//   usage: rand_gen <output.s> [seed] [num_instructions]
//
// If num_instructions is omitted, a random body length of 10..15 is used.
// Same seed + length => identical program.
//
// Every program is guaranteed to contain at least one load, one store and one forward branch.
// No ecall is emitted: the program simply ends after the last instruction.
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace
{
constexpr int BASE_ADDR = 1024;
constexpr int WINDOW = 256;
constexpr int MIN_LEN = 10;
constexpr int MAX_LEN = 30;

const char *BASE_REG = "s11";

const std::vector<std::string> POOL = {"t0", "t1", "t2", "s0", "s1", "a1", "a2", "a3"};

const std::vector<std::string> R_OPS = {"add", "sub", "and", "or",  "xor",  "sll",  "srl",
                                        "sra", "slt", "sltu"};
const std::vector<std::string> I_OPS = {"addi", "andi", "ori", "xori", "slti", "sltiu"};
const std::vector<std::string> SHIFT_I_OPS = {"slli", "srli", "srai"};
const std::vector<std::string> BRANCH_OPS = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};

struct MemOp
{
    const char *name;
    int size;
    bool store;
};
const std::vector<MemOp> LOAD_OPS = {{"lb", 1, false}, {"lbu", 1, false}, {"lh", 2, false},
                                     {"lhu", 2, false}, {"lw", 4, false}, {"lwu", 4, false},
                                     {"ld", 8, false}};
const std::vector<MemOp> STORE_OPS = {{"sb", 1, true}, {"sh", 2, true}, {"sw", 4, true},
                                      {"sd", 8, true}};

std::mt19937_64 rng;

int rnd(int lo, int hi) { return std::uniform_int_distribution<int>(lo, hi)(rng); }

template <typename T>
const T &pick(const std::vector<T> &v)
{
    return v[rnd(0, static_cast<int>(v.size()) - 1)];
}

std::string srcReg() { return rnd(0, 11) == 0 ? "zero" : pick(POOL); }
std::string dstReg() { return pick(POOL); }

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

enum Kind { RANDOM = -1, FORCE_LOAD, FORCE_STORE, FORCE_BRANCH };
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
    rng.seed(seed);

    int length = argc > 3 ? std::atoi(argv[3]) : rnd(MIN_LEN, MAX_LEN);
    if (length < 1)
    {
        std::cerr << "num_instructions must be >= 1\n";
        return 1;
    }

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

    std::vector<int> slotKind(length, RANDOM);
    {
        std::vector<int> idx(length);
        for (int i = 0; i < length; ++i)
            idx[i] = i;
        std::shuffle(idx.begin(), idx.end(), rng);
        const int forced[] = {FORCE_STORE, FORCE_LOAD, FORCE_BRANCH};
        for (int k = 0; k < 3 && k < length; ++k)
            slotKind[idx[k]] = forced[k];
    }

    std::vector<PendingLabel> pending;
    int labelCounter = 0;

    auto emitMem = [&](bool store) {
        const MemOp &m = store ? pick(STORE_OPS) : pick(LOAD_OPS);
        const int offset = rnd(0, WINDOW / m.size - 1) * m.size;
        out << m.name << " " << (store ? srcReg() : dstReg()) << ", " << offset << "(" << BASE_REG
            << ")\n";
    };
    auto emitBranch = [&](int i) {
        std::string label = "L" + std::to_string(labelCounter++);
        out << pick(BRANCH_OPS) << " " << srcReg() << ", " << srcReg() << ", " << label << "\n";
        pending.push_back({i + 1 + rnd(1, 3), label});
    };

    for (int i = 0; i < length; ++i)
    {
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

        if (slotKind[i] == FORCE_LOAD) { emitMem(false); continue; }
        if (slotKind[i] == FORCE_STORE) { emitMem(true); continue; }
        if (slotKind[i] == FORCE_BRANCH) { emitBranch(i); continue; }

        const int kind = rnd(0, 99);
        if (kind < 35)
            out << pick(R_OPS) << " " << dstReg() << ", " << srcReg() << ", " << srcReg() << "\n";
        else if (kind < 55)
            out << pick(I_OPS) << " " << dstReg() << ", " << srcReg() << ", " << rnd(-2048, 2047)
                << "\n";
        else if (kind < 63)
            out << pick(SHIFT_I_OPS) << " " << dstReg() << ", " << srcReg() << ", " << rnd(0, 31)
                << "\n";
        else if (kind < 68)
            out << "li " << dstReg() << ", " << interestingValue() << "\n";
        else if (kind < 72)
            out << "mv " << dstReg() << ", " << srcReg() << "\n";
        else if (kind < 84)
            emitMem(rnd(0, 1) == 1);
        else
            emitBranch(i);
    }

    // Labels still pending resolve at the end; a nop gives them an instruction to point at.
    if (!pending.empty())
    {
        for (const auto &p : pending)
            out << p.name << ":\n";
        out << "nop\n";
    }

    return out ? 0 : 1;
}