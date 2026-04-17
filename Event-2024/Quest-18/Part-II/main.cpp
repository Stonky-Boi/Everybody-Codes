#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

struct point
{
    int row;
    int column;
    int time;
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    string line;
    while (getline(input_file, line))
    {
        if (!line.empty())
            grid.push_back(line);
    }
    int rows = grid.size();
    int columns = grid[0].size();
    queue<point> q;
    vector<vector<bool>> visited(rows, vector<bool>(columns, false));
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == '.')
            {
                bool is_edge = (r == 0 || r == rows - 1 || c == 0 || c == columns - 1);
                if (is_edge)
                {
                    q.push({r, c, 0});
                    visited[r][c] = true;
                }
            }
        }
    }
    int row_offsets[] = {-1, 1, 0, 0};
    int column_offsets[] = {0, 0, -1, 1};
    int max_time = 0;
    int palms_watered = 0;
    while (!q.empty())
    {
        point curr = q.front();
        q.pop();
        if (grid[curr.row][curr.column] == 'P')
        {
            palms_watered++;
            if (curr.time > max_time)
                max_time = curr.time;
        }
        for (int i = 0; i < 4; i++)
        {
            int next_row = curr.row + row_offsets[i];
            int next_column = curr.column + column_offsets[i];
            if (next_row >= 0 && next_row < rows && next_column >= 0 && next_column < columns)
            {
                if (!visited[next_row][next_column])
                {
                    if (grid[next_row][next_column] == '.' || grid[next_row][next_column] == 'P')
                    {
                        visited[next_row][next_column] = true;
                        q.push({next_row, next_column, curr.time + 1});
                    }
                }
            }
        }
    }
    output_file << max_time;
    return 0;
}