// Block-structured random RISC-V program generator (human-style code) for Kites differential testing.
//
//   usage: rand_gen2 <output.s> [seed] [num_instructions]
//
// Same CLI as rand_gen.cpp, so it works with the tester script unchanged.
// num_instructions is the approximate number of static instructions (programs may overshoot by
// a few instructions because blocks are emitted whole). If omitted, 40..120 is used.
// Same seed + length => identical program.
//
// Instead of preloading every register, the program is a sequence of small "blocks"
// (init, ALU chains, array fill/sum/copy, if-then, if-else, min/max select, bit mixing and
// counted loops). Each block reads registers produced by earlier blocks (recently written
// registers are preferred), so there are real dependency chains across blocks.
//
// Guarantees: at least one load, one store, one forward branch and one backward loop branch.
// All loops are counted (counter in s9, pointer in s10, never touched elsewhere) so they always
// terminate. No ecall: the program just ends after the last instruction.
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
    constexpr int WINDOW = 512;        // bytes of data memory used, starting at BASE_REG
    constexpr int MIN_LEN = 40;
    constexpr int MAX_LEN = 120;

    const std::string BASE_REG = "s11";
    const std::string LOOP_CNT = "s9";
    const std::string LOOP_PTR = "s10";

    // value registers (s9, s10, s11 are reserved)
    const std::vector<std::string> POOL = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "a0", "a1", "a2",
        "a3", "a4", "a5", "a6", "a7", "s0", "s1", "s2", "s3", "s4",
        "s5", "s6", "s7", "s8"};

        const std::vector<std::string> R_OPS = {"add", "sub", "and", "or", "xor", "sll", "srl", "sra", "slt", "sltu"};
        const std::vector<std::string> R_ARITH = {"add", "add", "sub", "xor", "or", "and"};
        const std::vector<std::string> I_OPS = {"addi", "addi", "addi", "andi", "ori", "xori", "slti", "sltiu"};
        const std::vector<std::string> SHIFT_I = {"slli", "srli", "srai"};
        const std::vector<std::string> BRANCH_OPS = {"beq", "bne", "blt", "bge", "bltu", "bgeu"};

        struct MemOp { const char *name; int size; };
        const std::vector<MemOp> LOADS = {{"lw", 4}, {"ld", 8}, {"lw", 4}, {"lb", 1}, {"lbu", 1},
        {"lh", 2}, {"lhu", 2}, {"lwu", 4}};
        const std::vector<MemOp> STORES = {{"sw", 4}, {"sd", 8}, {"sw", 4}, {"sb", 1}, {"sh", 2}};

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

        struct Gen
        {
            std::ofstream out;
            int count = 0;
            int labels = 0;
            bool labelPending = false;
            std::vector<std::string> live; // most recently written first
            int regionOff = 0;             // last memory region written (for store->load reuse)
            bool hasLoad = false, hasStore = false, hasFwd = false, hasLoop = false;

            void emit(const std::string &s)
            {
                out << "    " << s << "\n";
                ++count;
                labelPending = false;
            }
            void label(const std::string &l)
            {
                out << l << ":\n";
                labelPending = true;
            }
            std::string newLabel(const char *p) { return std::string(p) + std::to_string(labels++); }

            void markLive(const std::string &r)
            {
                live.erase(std::remove(live.begin(), live.end(), r), live.end());
                live.insert(live.begin(), r);
                if (live.size() > 14) live.pop_back();
            }
            std::string fresh()
            {
                std::string r = pick(POOL);
                return r;
            }
            // destination: either overwrite something live (keeps chains going) or a new register
            std::string dst()
            {
                std::string r = (!live.empty() && chance(40)) ? live[rnd(0, (int)live.size() - 1)] : fresh();
                return r;
            }
            // source: biased to the most recently produced values
            std::string src()
            {
                if (chance(6)) return "zero";
                if (live.empty())
                {
                    std::string r = fresh();
                    emit("li " + r + ", " + std::to_string(interesting()));
                    markLive(r);
                    return r;
                }
                int idx = 0;
                while (idx < (int)live.size() - 1 && chance(45)) ++idx;
                return live[idx];
            }

            // one random ALU instruction; a (if non-empty) is forced as first source
            std::string aluInstr(const std::string &d, const std::string &a)
            {
                const std::string s1 = a.empty() ? src() : a;
                const int k = rnd(0, 99);
                if (k < 45) return pick(R_OPS) + " " + d + ", " + s1 + ", " + src();
                if (k < 80) return pick(I_OPS) + " " + d + ", " + s1 + ", " + std::to_string(rnd(-2048, 2047));
                return pick(SHIFT_I) + " " + d + ", " + s1 + ", " + std::to_string(chance(25) ? rnd(32, 63) : rnd(0, 31));
            }

            // small immediates are more "human" for add/sub chains
            std::string smallImm() { return std::to_string(rnd(-16, 64)); }

            // ---------------- blocks ----------------
            void initBlock()
            {
                int n = rnd(2, 4);
                for (int i = 0; i < n; ++i)
                {
                    std::string r = fresh();
                    emit("li " + r + ", " + std::to_string(interesting()));
                    markLive(r);
                }
            }

            void aluChain()
            {
                int n = rnd(3, 7);
                std::string prev = src();
                for (int i = 0; i < n; ++i)
                {
                    std::string d = (i == n - 1 || chance(50)) ? dst() : fresh();
                    if (chance(35))
                        emit("addi " + d + ", " + prev + ", " + smallImm());
                    else
                        emit(aluInstr(d, prev));
                    markLive(d);
                    prev = d;
                }
            }

            void bitMix()
            {
                std::string a = src(), t = fresh();
                emit(pick(SHIFT_I) + " " + t + ", " + a + ", " + std::to_string(rnd(1, 31)));
                markLive(t);
                std::string u = fresh();
                emit(std::string(chance(50) ? "xor " : "or ") + u + ", " + t + ", " + src());
                markLive(u);
                std::string v = dst();
                emit(std::string(chance(50) ? "andi " : "xori ") + v + ", " + u + ", " + std::to_string(rnd(1, 2047)));
                markLive(v);
                if (chance(50))
                {
                    std::string w = dst();
                    emit("sltu " + w + ", " + v + ", " + src());
                    markLive(w);
                }
            }

            void doStore(const MemOp &m, int off, const std::string &v)
            {
                emit(std::string(m.name) + " " + v + ", " + std::to_string(off) + "(" + BASE_REG + ")");
                hasStore = true;
            }
            void doLoad(const MemOp &m, int off, const std::string &d)
            {
                emit(std::string(m.name) + " " + d + ", " + std::to_string(off) + "(" + BASE_REG + ")");
                markLive(d);
                hasLoad = true;
            }

            void arrayFill()
            {
                int n = rnd(3, 6);
                int base = rnd(0, WINDOW / 8 - 12) * 8;
                const MemOp &m = pick(STORES);
                for (int i = 0; i < n; ++i)
                {
                    std::string v = src();
                    if (chance(40)) // compute the element first
                    {
                        std::string t = fresh();
                        emit("addi " + t + ", " + v + ", " + std::to_string(i * rnd(1, 7)));
                        markLive(t);
                        v = t;
                    }
                    doStore(m, base + i * m.size, v);
                }
                regionOff = base;
            }

            void arraySum()
            {
                int n = rnd(3, 5);
                int base = chance(60) ? regionOff : rnd(0, WINDOW / 8 - 12) * 8;
                const MemOp &m = pick(LOADS);
                std::string acc = fresh();
                for (int i = 0; i < n; ++i)
                {
                    std::string t = fresh();
                    if (t == acc) t = (acc == "t0") ? "t1" : "t0";
                    doLoad(m, base + i * m.size, t);
                    if (i == 0)
                    {
                        emit("mv " + acc + ", " + t);
                        markLive(acc);
                    }
                    else
                    {
                        emit(std::string(pick(R_ARITH)) + " " + acc + ", " + acc + ", " + t);
                        markLive(acc);
                    }
                }
            }

            void copyBlock()
            {
                int n = rnd(2, 4);
                int from = rnd(0, 20) * 8, to = 256 + rnd(0, 20) * 8;
                const MemOp &l = pick(LOADS);
                // store with the same width
                const char *sname = l.size == 1 ? "sb" : l.size == 2 ? "sh" : l.size == 4 ? "sw" : "sd";
                MemOp s{sname, l.size};
                for (int i = 0; i < n; ++i)
                {
                    std::string t = fresh();
                    doLoad(l, from + i * l.size, t);
                    if (chance(40))
                        emit("addi " + t + ", " + t + ", " + smallImm());
                    doStore(s, to + i * l.size, t);
                }
                regionOff = to;
            }

            void ifThen()
            {
                std::string L = newLabel("Lskip");
                emit(pick(BRANCH_OPS) + " " + src() + ", " + src() + ", " + L);
                hasFwd = true;
                int n = rnd(1, 4);
                for (int i = 0; i < n; ++i)
                {
                    if (chance(20)) { // sometimes a memory access inside the guarded region
                        if (chance(50)) doStore(pick(STORES), rnd(0, WINDOW / 8 - 1) * 8, src());
                        else doLoad(pick(LOADS), rnd(0, WINDOW / 8 - 1) * 8, dst());
                        continue;
                    }
                    std::string d = dst();
                    emit(aluInstr(d, ""));
                    markLive(d);
                }
                label(L);
            }

            void ifElse()
            {
                std::string Le = newLabel("Lelse"), Ln = newLabel("Lend");
                emit(pick(BRANCH_OPS) + " " + src() + ", " + src() + ", " + Le);
                hasFwd = true;
                std::string d = dst(); // both arms define the same result register
                int n = rnd(1, 3);
                for (int i = 0; i < n; ++i) emit(aluInstr(d, i ? d : ""));
                emit("j " + Ln);
                label(Le);
                n = rnd(1, 3);
                for (int i = 0; i < n; ++i) emit(aluInstr(d, i ? d : ""));
                label(Ln);
                markLive(d);
            }

            void minMax() // d = max/min-like select using a compare + branch
            {
                std::string a = src(), b = src();
                std::string d = dst();
                std::string L = newLabel("Lsel");
                emit("mv " + d + ", " + a);
                emit(std::string(chance(50) ? "bge " : "blt ") + d + ", " + b + ", " + L);
                hasFwd = true;
                emit("mv " + d + ", " + b);
                label(L);
                markLive(d);
            }

            // counted loop; always terminates (s9 counts down, s10 walks memory)
            void loopBlock()
            {
                hasLoop = true;
                std::string L = newLabel("Lloop");
                int iters = rnd(2, 6);
                int variant = rnd(0, 3);
                int sz = chance(50) ? 4 : 8;
                int off = rnd(0, (WINDOW - 8 * 8 - 64) / 8) * 8; // room for 6 iterations * 8 bytes
                std::string acc = fresh();
                std::string t = fresh();
                if (t == acc) t = (acc == "t0") ? "t1" : "t0";

                emit("li " + LOOP_CNT + ", " + std::to_string(iters));
                if (variant != 3) emit("addi " + LOOP_PTR + ", " + BASE_REG + ", " + std::to_string(off));
                if (variant == 0 || variant == 3)
                {
                    if (chance(50) && !live.empty()) emit("mv " + acc + ", " + src());
                    else emit("li " + acc + ", " + std::to_string(rnd(0, 10)));
                }
                label(L);
                const char *ld = sz == 4 ? "lw" : "ld";
                const char *st = sz == 4 ? "sw" : "sd";
                if (variant == 0) // sum reduction over memory
                {
                    emit(std::string(ld) + " " + t + ", 0(" + LOOP_PTR + ")");
                    emit("add " + acc + ", " + acc + ", " + t);
                    if (chance(40)) emit("xor " + acc + ", " + acc + ", " + src());
                    hasLoad = true;
                }
                else if (variant == 1) // fill memory with a running value
                {
                    std::string v = src();
                    emit("addi " + t + ", " + v + ", " + std::to_string(rnd(1, 9)));
                    emit(std::string(st) + " " + t + ", 0(" + LOOP_PTR + ")");
                    if (chance(50)) emit("add " + t + ", " + t + ", " + t);
                    hasStore = true;
                    acc = t;
                }
                else if (variant == 2) // in-place update: load, modify, store back
                {
                    emit(std::string(ld) + " " + t + ", 0(" + LOOP_PTR + ")");
                    emit(chance(50) ? "addi " + t + ", " + t + ", " + smallImm() : "slli " + t + ", " + t + ", 1");
                    emit(std::string(st) + " " + t + ", 0(" + LOOP_PTR + ")");
                    hasLoad = hasStore = true;
                    acc = t;
                }
                else // pure ALU loop (no memory): e.g. accumulate and mix
                {
                    emit("add " + acc + ", " + acc + ", " + LOOP_CNT);
                    emit(std::string(chance(50) ? "slli " : "srli ") + t + ", " + acc + ", " + std::to_string(rnd(1, 4)));
                    emit("xor " + acc + ", " + acc + ", " + t);
                }
                if (variant != 3) emit("addi " + LOOP_PTR + ", " + LOOP_PTR + ", " + std::to_string(sz));
                emit("addi " + LOOP_CNT + ", " + LOOP_CNT + ", -1");
                emit("bne " + LOOP_CNT + ", zero, " + L); // backward branch
                markLive(acc);
                if (variant == 0 || variant == 3) {} else markLive(t);
                regionOff = off;
            }

            void randomBlock()
            {
                int k = rnd(0, 99);
                if (k < 18) aluChain();
                else if (k < 26) bitMix();
                else if (k < 36) arrayFill();
                else if (k < 46) arraySum();
                else if (k < 53) copyBlock();
                else if (k < 66) ifThen();
                else if (k < 74) ifElse();
                else if (k < 80) minMax();
                else if (k < 82) initBlock();
                else loopBlock();
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
    const uint64_t maxCodeBytes = static_cast<uint64_t>(length + 60) * 32 + 1024;
    const uint64_t baseAddr = TEXT_START + ((maxCodeBytes + 63) & ~63ULL);

    Gen g;
    g.out.open(outPath);
    if (!g.out)
    {
        std::cerr << "cannot open " << outPath << " for writing\n";
        return 1;
    }
    g.out << "# rand_gen2 seed=" << seed << " length=" << length << " baseAddr=" << baseAddr << "\n";
    g.emit("li " + BASE_REG + ", " + std::to_string(baseAddr));

    g.initBlock(); // a program starts by setting up a few inputs, like a human would
    while (g.count < length)
        g.randomBlock();

    // make sure the required features are present
    if (!g.hasStore) g.arrayFill();
    if (!g.hasLoad) g.arraySum();
    if (!g.hasFwd) g.ifThen();
    if (!g.hasLoop) g.loopBlock();

    if (g.labelPending) g.emit("nop"); // a trailing label needs an instruction to point at
    return g.out ? 0 : 1;
}
