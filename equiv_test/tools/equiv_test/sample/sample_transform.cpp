// Example "your own C++ code" for run_equiv.py.
//
// Contract: it is invoked as   sample_transform <input.s> <output.s> [--inject-bug]
// It reads the input text file and writes a NEW text file. Here the rewrite is a
// semantics-preserving clean-up: strip comments / blank lines and turn
// `mv rd, rs` into `addi rd, rs, 0`.
//
// With --inject-bug it deliberately corrupts the first `li`, so you can see the
// runner report a FAIL.  Replace the body of transform() with your own logic.
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

static std::string transform(const std::string &line, bool &bugPending)
{
    std::string s = line.substr(0, line.find('#'));
    s = std::regex_replace(s, std::regex(R"(^\s+|\s+$)"), "");
    if (s.empty())
        return s;

    std::smatch m;
    if (std::regex_match(s, m, std::regex(R"(mv\s+(\w+)\s*,\s*(\w+))")))
        return "addi " + m[1].str() + ", " + m[2].str() + ", 0";

    if (bugPending && std::regex_match(s, m, std::regex(R"(li\s+(\w+)\s*,\s*(-?\d+))")))
    {
        bugPending = false;
        return "li " + m[1].str() + ", " + std::to_string(std::stoll(m[2].str()) + 1);
    }
    return s;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <input> <output> [--inject-bug]\n";
        return 1;
    }
    bool bugPending = argc > 3 && std::string(argv[3]) == "--inject-bug";

    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    if (!in || !out)
    {
        std::cerr << "cannot open input/output file\n";
        return 1;
    }
    std::string line;
    while (std::getline(in, line))
    {
        std::string t = transform(line, bugPending);
        if (!t.empty())
            out << t << "\n";
    }
    return 0;
}
