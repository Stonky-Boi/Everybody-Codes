#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> lines;
    string line;
    while (getline(input_file, line))
    {
        if (!line.empty())
            lines.push_back(line);
    }
    vector<vector<long long>> grid;
    for (const string &l : lines)
    {
        stringstream ss(l);
        long long value;
        vector<long long> row;
        while (ss >> value)
            row.push_back(value);
        grid.push_back(row);
    }
    int num_cols = grid[0].size();
    vector<vector<long long>> columns(num_cols);
    for (size_t r = 0; r < grid.size(); r++)
    {
        for (int c = 0; c < num_cols; c++)
            columns[c].push_back(grid[r][c]);
    }
    long long final_number = 0;
    for (int round = 1; round <= 10; round++)
    {
        int clapper_col = (round - 1) % num_cols;
        int target_col = (clapper_col + 1) % num_cols;
        long long clapper_value = columns[clapper_col].front();
        columns[clapper_col].erase(columns[clapper_col].begin());
        int L = columns[target_col].size();
        long long claps = clapper_value;
        if (L == 0)
            columns[target_col].push_back(clapper_value);
        else
        {
            long long i = ((claps - 1) % (2 * L) + 2 * L) % (2 * L);
            int insert_index = 0;
            if (i < L)
                insert_index = i;
            else
                insert_index = 2 * L - i;
            columns[target_col].insert(columns[target_col].begin() + insert_index, clapper_value);
        }
        string s = "";
        for (int c = 0; c < num_cols; c++)
        {
            if (!columns[c].empty())
                s += to_string(columns[c].front());
        }
        final_number = stoll(s);
    }
    output_file << final_number;
    return 0;
}