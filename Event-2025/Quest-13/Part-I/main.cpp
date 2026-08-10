#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<int> instructions;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        instructions.push_back(stoi(line));
    }
    int spots = instructions.size() + 1;
    vector<int> wheel(spots, 0);
    wheel[0] = 1;
    int clockwise = 1;
    int counterclockwise = spots - 1;
    for (int i = 0; i < instructions.size(); i++)
    {
        if (i % 2 == 0)
        {
            wheel[clockwise] = instructions[i];
            clockwise++;
        }
        else
        {
            wheel[counterclockwise] = instructions[i];
            counterclockwise--;
        }
    }
    int target = 2025;
    int final_position = target % spots;
    output_file << wheel[final_position] << endl;
    return 0;
}