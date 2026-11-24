// Random RISC-V program generator for Kites differential testing (short-program version, no branches/ecall).
//
//   usage: rand_gen <output.s> [seed] [num_instructions]
//
// If num_instructions is omitted, a random body length of 50..100 is used.
// Same seed + length => identical program.
//
// Every program is guaranteed to contain at least one load and one store.
// No ecall or branches are emitted: the program simply runs straight-line and ends.
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
    constexpr uint64_t TEXT_START = 0; // Adjust if your simulator loads .text at a non-zero base (e.g., 0x80000000)
    constexpr int WINDOW = 256;
    constexpr int MIN_LEN = 50;
    constexpr int MAX_LEN = 100;

    const char *BASE_REG = "s11";

    const std::vector<std::string> POOL = {"t0", "t1", "t2", "s0", "s1", "a1", "a2", "a3"};

    const std::vector<std::string> R_OPS = {"add", "sub", "and", "or",  "xor",  "sll",  "srl",
        "sra", "slt", "sltu"};
        const std::vector<std::string> I_OPS = {"addi", "andi", "ori", "xori", "slti", "sltiu"};
        const std::vector<std::string> SHIFT_I_OPS = {"slli", "srli", "srai"};

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

        enum Kind { RANDOM = -1, FORCE_LOAD, FORCE_STORE };
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

    // Dynamically compute baseAddr beyond the worst-case expanded instruction footprint
    const uint64_t maxCodeBytes = static_cast<uint64_t>(length + 10) * 32 + 1024;
    const uint64_t baseAddr = TEXT_START + ((maxCodeBytes + 63) & ~63ULL);

    std::ofstream out(outPath);
    if (!out)
    {
        std::cerr << "cannot open " << outPath << " for writing\n";
        return 1;
    }

    out << "# rand_gen seed=" << seed << " length=" << length << " baseAddr=" << baseAddr << "\n";
    out << "li " << BASE_REG << ", " << baseAddr << "\n";
    for (const auto &r : POOL)
        out << "li " << r << ", " << interestingValue() << "\n";

    std::vector<int> slotKind(length, RANDOM);
    {
        std::vector<int> idx(length);
        for (int i = 0; i < length; ++i)
            idx[i] = i;
        std::shuffle(idx.begin(), idx.end(), rng);
        const int forced[] = {FORCE_STORE, FORCE_LOAD};
        for (int k = 0; k < 2 && k < length; ++k)
            slotKind[idx[k]] = forced[k];
    }

    auto emitMem = [&](bool store) {
        const MemOp &m = store ? pick(STORE_OPS) : pick(LOAD_OPS);
        const int offset = rnd(0, WINDOW / m.size - 1) * m.size;
        out << m.name << " " << (store ? srcReg() : dstReg()) << ", " << offset << "(" << BASE_REG
        << ")\n";
    };

    for (int i = 0; i < length; ++i)
    {
        if (slotKind[i] == FORCE_LOAD) { emitMem(false); continue; }
        if (slotKind[i] == FORCE_STORE) { emitMem(true); continue; }

        const int kind = rnd(0, 99);
        if (kind < 40)
            out << pick(R_OPS) << " " << dstReg() << ", " << srcReg() << ", " << srcReg() << "\n";
        else if (kind < 65)
            out << pick(I_OPS) << " " << dstReg() << ", " << srcReg() << ", " << rnd(-2048, 2047)
            << "\n";
        else if (kind < 75)
            out << pick(SHIFT_I_OPS) << " " << dstReg() << ", " << srcReg() << ", " << rnd(0, 31)
            << "\n";
        else if (kind < 82)
            out << "li " << dstReg() << ", " << interestingValue() << "\n";
        else if (kind < 88)
            out << "mv " << dstReg() << ", " << srcReg() << "\n";
        else
            emitMem(rnd(0, 1) == 1);
    }

    return out ? 0 : 1;
}
