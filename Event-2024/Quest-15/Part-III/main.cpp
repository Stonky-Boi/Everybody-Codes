#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <map>
using namespace std;

struct state
{
    int x;
    int y;
    int mask;
    int distance;
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
    int start_x = -1;
    int start_y = 0;
    for (int c = 0; c < columns; c++)
    {
        if (grid[0][c] == '.')
        {
            start_x = c;
            break;
        }
    }
    map<char, int> herb_types;
    int herb_count = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            char ch = grid[r][c];
            if (ch >= 'A' && ch <= 'Z')
            {
                if (herb_types.find(ch) == herb_types.end())
                {
                    herb_types[ch] = herb_count;
                    herb_count++;
                }
            }
        }
    }
    int target_mask = (1 << herb_count) - 1;
    int start_mask = 0;
    queue<state> q;
    vector<vector<vector<bool>>> visited(rows, vector<vector<bool>>(columns, vector<bool>(1 << herb_count, false)));
    q.push({start_x, start_y, start_mask, 0});
    visited[start_y][start_x][start_mask] = true;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int min_distance = -1;
    while (!q.empty())
    {
        state curr = q.front();
        q.pop();
        if (curr.x == start_x && curr.y == start_y && curr.mask == target_mask)
        {
            min_distance = curr.distance;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (nx >= 0 && nx < columns && ny >= 0 && ny < rows)
            {
                char ch = grid[ny][nx];
                if (ch != '#' && ch != '~')
                {
                    int next_mask = curr.mask;
                    if (ch >= 'A' && ch <= 'Z')
                        next_mask |= (1 << herb_types[ch]);
                    if (!visited[ny][nx][next_mask])
                    {
                        visited[ny][nx][next_mask] = true;
                        q.push({nx, ny, next_mask, curr.distance + 1});
                    }
                }
            }
        }
    }
    output_file << min_distance;
    return 0;
}