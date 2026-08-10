#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    set<int> crates;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int start = 0;
        int comma = line.find(',');
        while (comma != string::npos)
        {
            if (comma > start)
                crates.insert(stoi(line.substr(start, comma - start)));
            start = comma + 1;
            comma = line.find(',', start);
        }
        if (start < line.length())
            crates.insert(stoi(line.substr(start)));
    }
    int max_sum = 0;
    for (int crate_size : crates)
        max_sum += crate_size;
    output_file << max_sum << endl;
    return 0;
}