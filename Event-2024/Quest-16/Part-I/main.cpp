#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    vector<int> advances;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ','))
        advances.push_back(stoi(token));
    int num_wheels = advances.size();
    vector<vector<string>> wheels(num_wheels);
    getline(input_file, line); // skip empty line
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        for (int i = 0; i < num_wheels; i++)
        {
            if (i * 4 < line.length())
            {
                string symbol = line.substr(i * 4, 3);
                if (symbol != "   " && !symbol.empty())
                    wheels[i].push_back(symbol);
            }
        }
    }
    string sequence = "";
    for (int i = 0; i < num_wheels; i++)
    {
        int length = wheels[i].size();
        if (length > 0)
        {
            int index = (100 * advances[i]) % length;
            sequence += wheels[i][index];
            if (i < num_wheels - 1)
                sequence += " ";
        }
    }
    output_file << sequence;
    return 0;
}