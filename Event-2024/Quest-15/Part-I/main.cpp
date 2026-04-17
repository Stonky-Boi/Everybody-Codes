#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

struct point
{
    int x;
    int y;
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
    int start_x = -1, start_y = -1;
    for (int c = 0; c < columns; c++)
    {
        if (grid[0][c] == '.')
        {
            start_x = c;
            start_y = 0;
            break;
        }
    }
    queue<point> q;
    vector<vector<bool>> visited(rows, vector<bool>(columns, false));
    q.push({start_x, start_y, 0});
    visited[start_y][start_x] = true;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int min_distance = -1;
    while (!q.empty())
    {
        point curr = q.front();
        q.pop();
        if (grid[curr.y][curr.x] == 'H')
        {
            min_distance = curr.distance * 2;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (nx >= 0 && nx < columns && ny >= 0 && ny < rows && !visited[ny][nx] && grid[ny][nx] != '#')
            {
                visited[ny][nx] = true;
                q.push({nx, ny, curr.distance + 1});
            }
        }
    }
    output_file << min_distance;
    return 0;
}