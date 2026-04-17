#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

long long process_grid(const vector<string> &grid)
{
    string result = "";
    for (int r = 2; r <= 5; r++)
    {
        for (int c = 2; c <= 5; c++)
        {
            string row_chars = "";
            row_chars += grid[r][0];
            row_chars += grid[r][1];
            row_chars += grid[r][6];
            row_chars += grid[r][7];
            string col_chars = "";
            col_chars += grid[0][c];
            col_chars += grid[1][c];
            col_chars += grid[6][c];
            col_chars += grid[7][c];
            char match = ' ';
            for (char rc : row_chars)
            {
                bool found = false;
                for (char cc : col_chars)
                {
                    if (rc == cc)
                    {
                        match = rc;
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
            }
            result += match;
        }
    }
    long long current_power = 0;
    for (size_t i = 0; i < result.length(); i++)
    {
        int value = result[i] - 'A' + 1;
        current_power += (i + 1) * value;
    }
    return current_power;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<vector<string>> current_grid;
    string line;
    long long total_power = 0;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (ss >> token)
            tokens.push_back(token);
        if (current_grid.empty())
            current_grid.resize(tokens.size());
        for (size_t i = 0; i < tokens.size(); i++)
            current_grid[i].push_back(tokens[i]);
        if (current_grid[0].size() == 8)
        {
            for (size_t i = 0; i < current_grid.size(); i++)
                total_power += process_grid(current_grid[i]);
            current_grid.clear();
        }
    }
    output_file << total_power;
    return 0;
}