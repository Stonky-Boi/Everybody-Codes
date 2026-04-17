#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <limits>
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
    vector<pair<int, int>> palm_trees;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == 'P')
                palm_trees.push_back({r, c});
        }
    }
    int num_palms = palm_trees.size();
    vector<vector<long long>> total_distances(rows, vector<long long>(columns, 0));
    vector<vector<int>> reach_counts(rows, vector<int>(columns, 0));
    int row_offsets[] = {-1, 1, 0, 0};
    int column_offsets[] = {0, 0, -1, 1};
    for (const auto &[start_row, start_column] : palm_trees)
    {
        vector<vector<bool>> visited(rows, vector<bool>(columns, false));
        queue<point> q;
        q.push({start_row, start_column, 0});
        visited[start_row][start_column] = true;
        while (!q.empty())
        {
            point curr = q.front();
            q.pop();
            if (grid[curr.row][curr.column] == '.')
            {
                total_distances[curr.row][curr.column] += curr.time;
                reach_counts[curr.row][curr.column]++;
            }
            for (int d = 0; d < 4; d++)
            {
                int next_row = curr.row + row_offsets[d];
                int next_col = curr.column + column_offsets[d];
                if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < columns)
                {
                    if (!visited[next_row][next_col])
                    {
                        if (grid[next_row][next_col] == '.' || grid[next_row][next_col] == 'P')
                        {
                            visited[next_row][next_col] = true;
                            q.push({next_row, next_col, curr.time + 1});
                        }
                    }
                }
            }
        }
    }
    long long min_distance = numeric_limits<long long>::max();
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == '.' && reach_counts[r][c] == num_palms)
            {
                if (total_distances[r][c] < min_distance)
                    min_distance = total_distances[r][c];
            }
        }
    }
    output_file << min_distance;
    return 0;
}