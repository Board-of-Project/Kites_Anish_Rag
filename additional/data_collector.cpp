#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

struct Data {
    string cycles;
    string ipc;
};

vector<Data> readFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening " << filename << '\n';
        exit(1);
    }

    vector<Data> data;
    string line;

    regex pattern(
        R"(Cycles\s*:\s*(\d+)\s+IPC\s+([-+]?\d*\.?\d+))"
    );

    while (getline(file, line)) {
        smatch match;

        if (regex_search(line, match, pattern)) {
            data.push_back({match[1].str(), match[2].str()});
        }
    }

    return data;
}

int main() {
    vector<Data> data1 = readFile("/tmp/comp_arch/cycles1.txt");
    vector<Data> data2 = readFile("/tmp/comp_arch/cycles2.txt");

    if (data1.size() != data2.size()) {
        cerr << "Error: The files contain different numbers of valid rows.\n";
        return 1;
    }

    ofstream output("/tmp/comp_arch/data.csv");

    if (!output) {
        cerr << "Error creating combined.csv\n";
        return 1;
    }

    output << "cycle1,cycle2,ipc1,ipc2\n";

    for (size_t i = 0; i < data1.size(); i++) {
        output << data1[i].cycles << ","
               << data2[i].cycles << ","
               << data1[i].ipc << ","
               << data2[i].ipc << '\n';
    }

    cout << "Created combined.csv with "
         << data1.size() << " rows.\n";

    return 0;
}
