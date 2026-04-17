#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cmath>
using namespace std;

int get_level(char c)
{
    if (c == 'S' || c == 'E')
        return 0;
    return c - '0';
}

struct state
{
    int distance;
    int x;
    int y;

    bool operator>(const state &other) const
    {
        return distance > other.distance;
    }
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
    int height = grid.size();
    int width = grid[0].size();
    int sx = -1, sy = -1;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            if (grid[r][c] == 'E')
            {
                sx = c;
                sy = r;
            }
        }
    }
    priority_queue<state, vector<state>, greater<state>> priority_q;
    vector<vector<int>> min_distances(height, vector<int>(width, 1000000000));
    priority_q.push({0, sx, sy});
    min_distances[sy][sx] = 0;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    int min_time = -1;
    while (!priority_q.empty())
    {
        state curr = priority_q.top();
        priority_q.pop();
        if (curr.distance > min_distances[curr.y][curr.x])
            continue;
        if (grid[curr.y][curr.x] == 'S')
        {
            min_time = curr.distance;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[ny][nx] != '#')
            {
                int level_curr = get_level(grid[curr.y][curr.x]);
                int level_next = get_level(grid[ny][nx]);
                int difference = abs(level_curr - level_next);
                int cost = min(difference, 10 - difference) + 1;
                if (curr.distance + cost < min_distances[ny][nx])
                {
                    min_distances[ny][nx] = curr.distance + cost;
                    priority_q.push({min_distances[ny][nx], nx, ny});
                }
            }
        }
    }
    output_file << min_time;
    return 0;
}