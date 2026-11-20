// Random RISC-V generator with controllable instruction mix, for Kites reorder experiments.
//
//   usage: rand_gen4 <output.s> [seed] [length] [branch_pct] [load_pct] [store_pct]
//
//   length      number of body instructions (default 100)
//   branch_pct  % of body instructions that are (forward) conditional branches (default 10)
//   load_pct    % of body instructions that are loads                            (default 25)
//   store_pct   % of body instructions that are stores                           (default 12)
//   everything else is ALU work (R-type / I-type / shifts / li / mv).
//
// The percentages are applied as exact counts (round(length*pct/100)) whose positions are
// shuffled, so a 0% setting really produces none of that instruction and results across
// programs have low variance. If the three percentages exceed 100 they are scaled down
// (branches first keep priority, then loads, then stores).
//
// Dependencies: sources are biased to recently written registers, so ALU results feed the next
// instructions and loads are often used right away (load-use). 40% of loads read an address a
// previous store wrote (same width), giving memory RAW dependencies.
// Branches are forward only (skip the next 1..3 instructions) so programs always terminate.
// No ecall: the program just ends after the last instruction.
// Same seed + same arguments => identical program.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace
{
    constexpr uint64_t TEXT_START = 0; // adjust if .text is loaded at a non-zero base
    constexpr int WINDOW = 256;

    const std::string BASE_REG = "s11";
    const std::vector<std::string> POOL = {"t0", "t1", "t2", "s0", "s1", "a1", "a2", "a3", "a4", "a5"};

    const std::vector<std::string> R_OPS = {"add", "add", "sub", "and", "or", "xor", "sll", "srl", "sra", "slt", "sltu"};
    const std::vector<std::string> I_OPS = {"addi", "addi", "andi", "ori", "xori", "slti", "sltiu"};
    const std::vector<std::string> SHIFT_I = {"slli", "srli", "srai"};
    const std::vector<std::string> BRANCH_OPS = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};

    struct MemOp { const char *ld, *st; int size; };
    const std::vector<MemOp> MEMS = {{"lb", "sb", 1}, {"lh", "sh", 2}, {"lw", "sw", 4},
                                     {"lw", "sw", 4}, {"ld", "sd", 8}};

    std::mt19937_64 rng;
    int rnd(int lo, int hi) { return std::uniform_int_distribution<int>(lo, hi)(rng); }
    bool chance(int pct) { return rnd(0, 99) < pct; }
    template <typename T> const T &pick(const std::vector<T> &v) { return v[rnd(0, (int)v.size() - 1)]; }

    int64_t interesting()
    {
        switch (rnd(0, 7))
        {
            case 0: return 0;
            case 1: return 1;
            case 2: return -1;
            case 3: return rnd(-2048, 2047);
            case 4: return rnd(0, 255);
            case 5: return INT32_MAX;
            case 6: return INT32_MIN;
            default: return (int64_t)rnd(-100000, 100000) * rnd(1, 500);
        }
    }

    enum Kind { ALU, LOAD, STORE, BRANCH };
    struct Stored { int off; const MemOp *m; };
    struct Pending { int due; std::string name; };
} // namespace

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <output.s> [seed] [length] [branch_pct] [load_pct] [store_pct]\n";
        return 1;
    }
    const std::string outPath = argv[1];
    const uint64_t seed = argc > 2 ? std::strtoull(argv[2], nullptr, 10) : std::random_device{}();
    const int length = argc > 3 ? std::atoi(argv[3]) : 100;
    double bp = argc > 4 ? std::atof(argv[4]) : 10.0;
    double lp = argc > 5 ? std::atof(argv[5]) : 25.0;
    double sp = argc > 6 ? std::atof(argv[6]) : 12.0;
    if (length < 1 || bp < 0 || lp < 0 || sp < 0)
    {
        std::cerr << "length must be >= 1 and percentages >= 0\n";
        return 1;
    }
    rng.seed(seed);

    int nb = (int)std::lround(length * bp / 100.0);
    int nl = (int)std::lround(length * lp / 100.0);
    int ns = (int)std::lround(length * sp / 100.0);
    nb = std::min(nb, length);
    nl = std::min(nl, length - nb);
    ns = std::min(ns, length - nb - nl);

    std::vector<int> kinds(length, ALU);
    {
        std::vector<int> idx(length);
        for (int i = 0; i < length; ++i) idx[i] = i;
        std::shuffle(idx.begin(), idx.end(), rng);
        int p = 0;
        for (int i = 0; i < nb; ++i) kinds[idx[p++]] = BRANCH;
        for (int i = 0; i < nl; ++i) kinds[idx[p++]] = LOAD;
        for (int i = 0; i < ns; ++i) kinds[idx[p++]] = STORE;
    }

    const uint64_t maxCodeBytes = static_cast<uint64_t>(length + 40) * 32 + 1024;
    const uint64_t baseAddr = TEXT_START + ((maxCodeBytes + 63) & ~63ULL);

    std::ofstream out(outPath);
    if (!out)
    {
        std::cerr << "cannot open " << outPath << " for writing\n";
        return 1;
    }
    out << "# rand_gen4 seed=" << seed << " length=" << length << " branch=" << nb << " load=" << nl
        << " store=" << ns << " baseAddr=" << baseAddr << "\n";
    out << "li " << BASE_REG << ", " << baseAddr << "\n";
    for (const auto &r : POOL) out << "li " << r << ", " << interesting() << "\n";

    std::vector<std::string> recent = POOL; // most recently written first
    auto mark = [&](const std::string &r) {
        recent.erase(std::remove(recent.begin(), recent.end(), r), recent.end());
        recent.insert(recent.begin(), r);
    };
    auto src = [&]() -> std::string {
        if (chance(8)) return "zero";
        int idx = 0;
        while (idx < (int)recent.size() - 1 && chance(45)) ++idx;
        return recent[idx];
    };
    auto dst = [&]() -> std::string { return pick(POOL); };

    std::vector<Stored> stored;
    std::vector<Pending> pending;
    int labels = 0;

    for (int i = 0; i < length; ++i)
    {
        for (auto it = pending.begin(); it != pending.end();)
        {
            if (it->due <= i) { out << it->name << ":\n"; it = pending.erase(it); }
            else ++it;
        }

        switch (kinds[i])
        {
            case LOAD:
            {
                const MemOp *m;
                int off;
                if (!stored.empty() && chance(40))
                {
                    const Stored &s = pick(stored);
                    m = s.m;
                    off = s.off;
                }
                else
                {
                    m = &pick(MEMS);
                    off = rnd(0, WINDOW / m->size - 1) * m->size;
                }
                std::string d = dst();
                out << m->ld << " " << d << ", " << off << "(" << BASE_REG << ")\n";
                mark(d);
                break;
            }
            case STORE:
            {
                const MemOp &m = pick(MEMS);
                int off = rnd(0, WINDOW / m.size - 1) * m.size;
                out << m.st << " " << src() << ", " << off << "(" << BASE_REG << ")\n";
                stored.push_back({off, &m});
                break;
            }
            case BRANCH:
            {
                std::string label = "L" + std::to_string(labels++);
                out << pick(BRANCH_OPS) << " " << src() << ", " << src() << ", " << label << "\n";
                pending.push_back({i + 1 + rnd(1, 3), label});
                break;
            }
            default:
            {
                std::string d = dst();
                int k = rnd(0, 99);
                if (k < 50) out << pick(R_OPS) << " " << d << ", " << src() << ", " << src() << "\n";
                else if (k < 75) out << pick(I_OPS) << " " << d << ", " << src() << ", " << rnd(-2048, 2047) << "\n";
                else if (k < 85) out << pick(SHIFT_I) << " " << d << ", " << src() << ", " << rnd(0, 31) << "\n";
                else if (k < 92) out << "li " << d << ", " << interesting() << "\n";
                else out << "mv " << d << ", " << src() << "\n";
                mark(d);
                break;
            }
        }
    }

    // labels still pending resolve at the end; a nop gives them an instruction to point at
    if (!pending.empty())
    {
        for (const auto &p : pending) out << p.name << ":\n";
        out << "nop\n";
    }
    return out ? 0 : 1;
}
