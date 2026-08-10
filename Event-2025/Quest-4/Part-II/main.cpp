#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<long long> gears;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        gears.push_back(stoll(line));
    }
    long long first_gear = gears.front();
    long long last_gear = gears.back();
    long long target_turns = 10000000000000LL;
    long long required_turns = (target_turns * last_gear + first_gear - 1) / first_gear;
    output_file << required_turns << endl;
    return 0;
}