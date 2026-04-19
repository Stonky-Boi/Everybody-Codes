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
    int num_tokens = tokens.size();
    vector<vector<int>> w_matrix(num_tokens, vector<int>(num_slots, 0));
    for (int i = 0; i < num_tokens; i++)
    {
        const string &token = tokens[i];
        for (int j = 0; j < num_slots; j++)
        {
            int column = j * 2;
            int index = 0;
            for (int row = 0; row < num_rows; row++)
            {
                if (grid[row][column] == '*')
                {
                    char dir = (index < token.size()) ? token[index++] : 'L';
                    if (dir == 'L')
                    {
                        if (column == 0)
                            column++;
                        else
                            column--;
                    }
                    else if (dir == 'R')
                    {
                        if (column == num_columns - 1)
                            column--;
                        else
                            column++;
                    }
                }
            }
            int final_slot = (column / 2) + 1;
            int toss_slot = j + 1;
            int coins = (final_slot * 2) - toss_slot;
            if (coins < 0)
                coins = 0;
            w_matrix[i][j] = coins;
        }
    }
    int target_mask = (1 << num_tokens) - 1;
    vector<int> dp_max(1 << num_tokens, -1000000000);
    vector<int> dp_min(1 << num_tokens, 1000000000);
    dp_max[0] = 0;
    dp_min[0] = 0;
    for (int slot = 0; slot < num_slots; slot++)
    {
        for (int mask = target_mask; mask >= 0; mask--)
        {
            for (int i = 0; i < num_tokens; i++)
            {
                if (!(mask & (1 << i)))
                {
                    int next_mask = mask | (1 << i);
                    if (dp_max[mask] != -1000000000)
                        dp_max[next_mask] = max(dp_max[next_mask], dp_max[mask] + w_matrix[i][slot]);
                    if (dp_min[mask] != 1000000000)
                        dp_min[next_mask] = min(dp_min[next_mask], dp_min[mask] + w_matrix[i][slot]);
                }
            }
        }
    }
    output_file << dp_min[target_mask] << " " << dp_max[target_mask];
    return 0;
}