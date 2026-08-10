#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
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
    vector<vector<bool>> visited(rows, vector<bool>(columns, false));
    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = true;
    q.push({rows - 1, columns - 1});
    visited[rows - 1][columns - 1] = true;
    int destroyed = 2;
    int row_moves[] = {-1, 1, 0, 0};
    int column_moves[] = {0, 0, -1, 1};
    while (!q.empty())
    {
        auto [curr_row, curr_column] = q.front();
        q.pop();
        char curr_size = grid[curr_row][curr_column];
        for (int i = 0; i < 4; i++)
        {
            int next_row = curr_row + row_moves[i];
            int next_column = curr_column + column_moves[i];
            if (next_row >= 0 && next_row < rows && next_column >= 0 && next_column < columns)
            {
                if (!visited[next_row][next_column] && grid[next_row][next_column] <= curr_size)
                {
                    visited[next_row][next_column] = true;
                    q.push({next_row, next_column});
                    destroyed++;
                }
            }
        }
    }
    output_file << destroyed << endl;
    return 0;
}