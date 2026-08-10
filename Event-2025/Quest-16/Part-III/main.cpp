#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    vector<int> target_wall;
    int position = 0;
    while (position < line.length())
    {
        int comma = line.find(',', position);
        if (comma == string::npos)
            comma = line.length();
        string token = line.substr(position, comma - position);
        if (!token.empty())
            target_wall.push_back(stoi(token));
        position = comma + 1;
    }
    vector<int> current_wall(target_wall.size(), 0);
    vector<int> spell_numbers;
    for (int i = 0; i < target_wall.size(); i++)
    {
        int column = i + 1;
        int difference = target_wall[i] - current_wall[i];
        if (difference > 0)
        {
            for (int k = 0; k < difference; k++)
                spell_numbers.push_back(column);
            for (int j = i; j < target_wall.size(); j += column)
                current_wall[j] += difference;
        }
    }
    long long target_blocks = 202520252025000LL;
    long long l = 0, r = target_blocks;
    long long max_length = 0;
    while (l <= r)
    {
        long long m = l + (r - l) / 2;
        long long curr_blocks = 0;
        for (int s : spell_numbers)
            curr_blocks += (m / s);
        if (curr_blocks <= target_blocks)
        {
            max_length = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    output_file << max_length << endl;
    return 0;
}