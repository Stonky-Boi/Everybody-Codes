#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        grid.push_back(line);
    }
    int rows = grid.size();
    int columns = grid[0].size();
    int active_tiles = 0;
    int row_moves[] = {-1, -1, 1, 1};
    int col_moves[] = {-1, 1, -1, 1};
    for (int round = 1; round <= 2025; round++)
    {
        vector<string> next_grid = grid;
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < columns; c++)
            {
                int active_neighbors = 0;
                for (int i = 0; i < 4; i++)
                {
                    int next_row = r + row_moves[i];
                    int next_col = c + col_moves[i];
                    if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < columns)
                    {
                        if (grid[next_row][next_col] == '#')
                            active_neighbors++;
                    }
                }
                bool active = (grid[r][c] == '#');
                bool odd_neighbours = (active_neighbors % 2 != 0);
                if (active == odd_neighbours)
                {
                    next_grid[r][c] = '#';
                    active_tiles++;
                }
                else
                    next_grid[r][c] = '.';
            }
        }
        grid = next_grid;
    }
    output_file << active_tiles << endl;
    return 0;
}