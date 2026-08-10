#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<int> gears;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        gears.push_back(stoi(line));
    }
    int first_gear = gears.front();
    int last_gear = gears.back();
    int first_rotations = 2025;
    int full_turns = (first_rotations * first_gear) / last_gear;
    output_file << full_turns << endl;
    return 0;
}