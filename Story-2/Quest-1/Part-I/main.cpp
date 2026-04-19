#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    vector<string> tokens;
    string line;
    bool parsing_grid = true;
    while (getline(input_file, line))
    {
        if (line.empty())
        {
            if (!grid.empty())
                parsing_grid = false;
            continue;
        }
        if (parsing_grid)
            grid.push_back(line);
        else
            tokens.push_back(line);
    }
    int num_rows = grid.size();
    int num_columns = grid[0].size();
    long long total_coins = 0;
    for (int i = 0; i < tokens.size(); i++)
    {
        int toss_slot = i + 1;
        int column = (toss_slot - 1) * 2;
        int row = 0;
        int index = 0;
        while (row < num_rows)
        {
            if (grid[row][column] == '*')
            {
                char direction = (index < tokens[i].size()) ? tokens[i][index++] : 'L';
                if (direction == 'L')
                {
                    if (column == 0)
                        column++;
                    else
                        column--;
                }
                else if (direction == 'R')
                {
                    if (column == num_columns - 1)
                        column--;
                    else
                        column++;
                }
            }
            row++;
        }
        int final_slot = (column / 2) + 1;
        int coins = (final_slot * 2) - toss_slot;
        if (coins < 0)
            coins = 0;
        total_coins += coins;
    }
    output_file << total_coins;
    return 0;
}