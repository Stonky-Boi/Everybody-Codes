#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> split_string(const string &input, char delimiter)
{
    vector<string> result;
    int start = 0;
    int end = input.find(delimiter);
    while (end != string::npos)
    {
        result.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(delimiter, start);
    }
    result.push_back(input.substr(start));
    return result;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<string> names;
    vector<string> instructions;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (names.empty())
            names = split_string(line, ',');
        else if (instructions.empty())
            instructions = split_string(line, ',');
    }
    int curr_index = 0;
    int max_index = names.size() - 1;
    for (const string &i : instructions)
    {
        char dir = i[0];
        int amount = stoi(i.substr(1));
        if (dir == 'R')
            curr_index = min(max_index, curr_index + amount);
        else if (dir == 'L')
            curr_index = max(0, curr_index - amount);
    }
    output_file << names[curr_index] << endl;
    return 0;
}