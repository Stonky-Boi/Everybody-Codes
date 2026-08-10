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
    int num_names = names.size();
    for (const string &i : instructions)
    {
        char dir = i[0];
        int amount = stoi(i.substr(1));
        int target_index = 0;
        if (dir == 'R')
            target_index = amount % num_names;
        else if (dir == 'L')
        {
            target_index = (-amount) % num_names;
            if (target_index < 0)
                target_index = (target_index % num_names + num_names) % num_names;
        }
        swap(names[0], names[target_index]);
    }
    output_file << names[0] << endl;
    return 0;
}