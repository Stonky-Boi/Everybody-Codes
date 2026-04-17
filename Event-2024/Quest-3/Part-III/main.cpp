#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    string line;
    while (input_file >> line)
        grid.push_back(line);
    int rows = grid.size();
    int columns = grid[0].size();
    vector<string> padded_grid;
    string empty_row(columns + 2, '.');
    padded_grid.push_back(empty_row);
    for (const string &r : grid)
        padded_grid.push_back("." + r + ".");
    padded_grid.push_back(empty_row);
    rows += 2;
    columns += 2;
    vector<vector<int>> dist(rows, vector<int>(columns, -1));
    queue<pair<int, int>> q;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (padded_grid[r][c] == '.')
            {
                dist[r][c] = 0;
                q.push({r, c});
            }
        }
    }
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < columns)
            {
                if (dist[nr][nc] == -1)
                {
                    dist[nr][nc] = dist[curr.first][curr.second] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
    long long total_blocks = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (dist[r][c] > 0)
                total_blocks += dist[r][c];
        }
    }
    output_file << total_blocks;
    return 0;
}