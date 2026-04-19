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
    int num_slots = (num_columns + 1) / 2;
    long long total_coins = 0;
    for (const string &t : tokens)
    {
        int max_coins = 0;
        for (int i = 1; i <= num_slots; i++)
        {
            int column = (i - 1) * 2;
            int index = 0;
            for (int row = 0; row < num_rows; row++)
            {
                if (grid[row][column] == '*')
                {
                    char direction = (index < t.size()) ? t[index++] : 'L';
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
            }
            int final_slot = (column / 2) + 1;
            int coins = (final_slot * 2) - i;
            if (coins < 0)
                coins = 0;
            if (coins > max_coins)
                max_coins = coins;
        }
        total_coins += max_coins;
    }
    output_file << total_coins;
    return 0;
}