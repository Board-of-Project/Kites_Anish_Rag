// Branch-free, block-structured random RISC-V generator for Kites reorder testing.
//
//   usage: rand_gen3 <output.s> [seed] [num_instructions]
//
// Same CLI as rand_gen.cpp / rand_gen2.cpp (works with tester2.sh unchanged).
// num_instructions is approximate (blocks are emitted whole). Default: 40..120.
// Same seed + length => identical program.
//
// Straight-line code only: no branches, jumps, loops or ecall. The program is a sequence of
// small blocks (load pairs, load-use chains, ALU chains, store runs, reload-from-stored-region,
// read-modify-write, multi-source merges, fresh independent chains). Every block takes its
// inputs from the results of SEVERAL earlier blocks (picked from the whole set of live results,
// not just the latest one), so the program contains many independent dependency chains that
// a reordering pass can interleave to hide load-use and ALU latencies. It also contains
// register WAR/WAW reuse and memory RAW dependencies (store -> later load of the same address).
//
// Guarantees: at least one load and one store.
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
    constexpr uint64_t TEXT_START = 0; // adjust if .text is loaded at a non-zero base
    constexpr int WINDOW = 512;        // bytes of data memory used from BASE_REG
    constexpr int MIN_LEN = 40;
    constexpr int MAX_LEN = 120;
    constexpr size_t MAX_LIVE = 12;    // live results at once (pool has 24 registers)

    const std::string BASE_REG = "s11";
    const std::vector<std::string> POOL = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "a0", "a1", "a2",
                                           "a3", "a4", "a5", "a6", "a7", "s0", "s1", "s2", "s3", "s4",
                                           "s5", "s6", "s7", "s8"};

    const std::vector<std::string> R_OPS = {"add", "add", "sub", "and", "or", "xor", "sll", "srl", "sra", "slt", "sltu"};
    const std::vector<std::string> I_OPS = {"addi", "addi", "andi", "ori", "xori", "slti", "sltiu"};
    const std::vector<std::string> SHIFT_I = {"slli", "srli", "srai"};

    struct MemOp { const char *ld, *ldu, *st; int size; };
    const std::vector<MemOp> MEMS = {{"lb", "lbu", "sb", 1}, {"lh", "lhu", "sh", 2},
                                     {"lw", "lwu", "sw", 4}, {"lw", "lwu", "sw", 4},
                                     {"ld", "ld", "sd", 8}};

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

    struct Region { int off, size, count; };

    struct Gen
    {
        std::ofstream out;
        int count = 0;
        std::vector<std::string> live;  // registers holding live results (oldest first)
        std::vector<Region> written;    // memory regions stored to so far
        bool hasLoad = false, hasStore = false;

        void emit(const std::string &s) { out << "    " << s << "\n"; ++count; }

        bool isLive(const std::string &r) const { return std::find(live.begin(), live.end(), r) != live.end(); }
        void push(const std::string &r)
        {
            live.erase(std::remove(live.begin(), live.end(), r), live.end());
            live.push_back(r);
            if (live.size() > MAX_LIVE) live.erase(live.begin());
        }
        void drop(const std::string &r) { live.erase(std::remove(live.begin(), live.end(), r), live.end()); }

        // a register that holds no live result (so it can be used as a temp / new result)
        std::string alloc()
        {
            for (int tries = 0; tries < 200; ++tries)
            {
                const std::string &r = pick(POOL);
                if (!isLive(r)) return r;
            }
            return POOL[0];
        }

        // n distinct live results (taken from anywhere in the live set); creates new
        // independent values with li if there are not enough.
        std::vector<std::string> sources(int n)
        {
            while ((int)live.size() < n)
            {
                std::string r = alloc();
                emit("li " + r + ", " + std::to_string(interesting()));
                push(r);
            }
            std::vector<std::string> v = live;
            std::shuffle(v.begin(), v.end(), rng);
            v.resize(n);
            return v;
        }

        // random ALU op: d = f(a, b) with b register or immediate
        void op(const std::string &d, const std::string &a, const std::string &b)
        {
            int k = rnd(0, 99);
            if (k < 60) emit(pick(R_OPS) + " " + d + ", " + a + ", " + b);
            else if (k < 85) emit(pick(I_OPS) + " " + d + ", " + a + ", " + std::to_string(rnd(-2048, 2047)));
            else emit(pick(SHIFT_I) + " " + d + ", " + a + ", " + std::to_string(rnd(0, 31)));
        }

        void load(const MemOp &m, int off, const std::string &d)
        {
            emit(std::string(chance(25) ? m.ldu : m.ld) + " " + d + ", " + std::to_string(off) + "(" + BASE_REG + ")");
            hasLoad = true;
        }
        void store(const MemOp &m, int off, const std::string &v)
        {
            emit(std::string(m.st) + " " + v + ", " + std::to_string(off) + "(" + BASE_REG + ")");
            hasStore = true;
        }
        int randOff(const MemOp &m) { return rnd(0, WINDOW / m.size - 1) * m.size; }

        // final result of a block: usually a fresh register, sometimes overwrites one of its own
        // sources (creates WAR / WAW register dependencies)
        std::string resultReg(const std::vector<std::string> &srcs)
        {
            if (!srcs.empty() && chance(25)) return pick(srcs);
            return alloc();
        }

        // ---------------- blocks ----------------
        void freshChain() // a new independent chain: li, li, op, op
        {
            std::string a = alloc();
            emit("li " + a + ", " + std::to_string(interesting()));
            push(a);
            std::string b = alloc();
            emit("li " + b + ", " + std::to_string(interesting()));
            push(b);
            std::string r = alloc();
            op(r, a, b);
            push(r);
        }

        void loadPair() // two loads then a use: load-use hazards, independent of earlier chains
        {
            const MemOp &m = pick(MEMS);
            std::string a = alloc();
            load(m, randOff(m), a);
            push(a);
            const MemOp &m2 = pick(MEMS);
            std::string b = alloc();
            load(m2, randOff(m2), b);
            push(b);
            auto s = sources(1);
            std::string r = chance(50) ? alloc() : a;
            emit(pick(R_OPS) + " " + r + ", " + a + ", " + b); // uses both loads right away
            push(r);
            if (chance(50)) { op(r, r, s[0]); push(r); }
        }

        void loadUse() // load feeding a dependent chain that also uses an older result
        {
            const MemOp &m = pick(MEMS);
            std::string t = alloc();
            load(m, randOff(m), t);
            push(t);
            auto s = sources(1);
            int n = rnd(2, 4);
            std::string prev = t;
            for (int i = 0; i < n; ++i)
            {
                std::string d = (i == n - 1) ? alloc() : alloc();
                op(d, prev, i % 2 == 0 ? s[0] : prev);
                push(d);
                prev = d;
            }
        }

        void aluChain() // dependent chain seeded by 1-3 earlier results
        {
            int k = rnd(1, 3);
            auto s = sources(k);
            std::string prev = s[0];
            int n = rnd(3, 6);
            for (int i = 0; i < n; ++i)
            {
                std::string other = (i + 1 < k) ? s[i + 1] : (chance(50) ? s[rnd(0, k - 1)] : prev);
                std::string d = (i == n - 1) ? resultReg(s) : alloc();
                op(d, prev, other);
                push(d);
                prev = d;
            }
        }

        void storeRun() // store several existing results to consecutive addresses
        {
            const MemOp &m = pick(MEMS);
            int k = rnd(2, 4);
            auto s = sources(k);
            int off = rnd(0, (WINDOW / m.size) - 5) * m.size;
            for (int i = 0; i < k; ++i) store(m, off + i * m.size, s[i]);
            written.push_back({off, m.size, k});
        }

        void reload() // read back a region written earlier (memory RAW) and combine with others
        {
            if (written.empty()) { storeRun(); return; }
            const Region &rg = pick(written);
            const MemOp *mp = nullptr;
            for (const auto &m : MEMS) if (m.size == rg.size) { mp = &m; break; }
            int k = rnd(1, std::min(rg.count, 3));
            std::vector<std::string> loaded;
            for (int i = 0; i < k; ++i)
            {
                std::string t = alloc();
                load(*mp, rg.off + i * rg.size, t);
                push(t);
                loaded.push_back(t);
            }
            auto s = sources(1);
            std::string acc = loaded[0];
            for (int i = 1; i < k; ++i)
            {
                std::string d = alloc();
                op(d, acc, loaded[i]);
                push(d);
                acc = d;
            }
            std::string r = alloc();
            op(r, acc, s[0]);
            push(r);
        }

        void rmw() // load, modify with an older result, store back to the same address
        {
            const MemOp &m = pick(MEMS);
            int off = (!written.empty() && chance(50))
                          ? 0 : randOff(m);
            if (off == 0 && !written.empty())
            {
                const Region &rg = pick(written);
                off = rg.off - rg.off % m.size;
            }
            std::string t = alloc();
            load(m, off, t);
            push(t);
            auto s = sources(1);
            std::string d = chance(50) ? t : alloc();
            op(d, t, s[0]);
            push(d);
            store(m, off, d);
            written.push_back({off, m.size, 1});
        }

        void merge() // combine 3-4 results from different earlier blocks (tree reduction)
        {
            int k = rnd(3, 4);
            auto s = sources(k);
            std::string t1 = alloc();
            op(t1, s[0], s[1]);
            push(t1);
            std::string t2 = alloc();
            op(t2, s[2], k == 4 ? s[3] : s[0]);
            push(t2);
            std::string r = resultReg({s[0], s[2]});
            op(r, t1, t2);
            // consume some inputs so registers are recycled (later WAW/WAR reuse)
            for (const auto &x : s) if (x != r && chance(40)) drop(x);
            push(r);
        }

        void randomBlock()
        {
            int k = rnd(0, 99);
            if (k < 17) loadPair();
            else if (k < 29) loadUse();
            else if (k < 43) aluChain();
            else if (k < 57) storeRun();
            else if (k < 67) reload();
            else if (k < 77) rmw();
            else if (k < 91) merge();
            else freshChain();
        }
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
    rng.seed(seed);

    int length = argc > 3 ? std::atoi(argv[3]) : rnd(MIN_LEN, MAX_LEN);
    if (length < 1)
    {
        std::cerr << "num_instructions must be >= 1\n";
        return 1;
    }

    // data window placed after the worst-case code size (li may expand to several instructions)
    const uint64_t maxCodeBytes = static_cast<uint64_t>(length + 40) * 32 + 1024;
    const uint64_t baseAddr = TEXT_START + ((maxCodeBytes + 63) & ~63ULL);

    Gen g;
    g.out.open(outPath);
    if (!g.out)
    {
        std::cerr << "cannot open " << outPath << " for writing\n";
        return 1;
    }
    g.out << "# rand_gen3 seed=" << seed << " length=" << length << " baseAddr=" << baseAddr << "\n";
    g.emit("li " + BASE_REG + ", " + std::to_string(baseAddr));

    // start with a few independent chains, then build on them
    int starts = rnd(2, 3);
    for (int i = 0; i < starts; ++i) g.freshChain();

    while (g.count < length) g.randomBlock();

    if (!g.hasStore) g.storeRun();
    if (!g.hasLoad) g.loadPair();

    return g.out ? 0 : 1;
}
