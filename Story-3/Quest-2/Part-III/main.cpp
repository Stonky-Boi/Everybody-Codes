#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

bool in_bounds(int x, int y, int size)
{
    return x >= 0 && x < size && y >= 0 && y < size;
}

void fill(vector<vector<bool>> &visited, int size)
{
    vector<vector<bool>> reachable(size, vector<bool>(size, false));
    queue<pair<int, int>> q;
    for (int i = 0; i < size; i++)
    {
        if (!visited[0][i])
        {
            reachable[0][i] = true;
            q.push({i, 0});
        }
        if (!visited[size - 1][i])
        {
            reachable[size - 1][i] = true;
            q.push({i, size - 1});
        }
        if (!visited[i][0])
        {
            reachable[i][0] = true;
            q.push({0, i});
        }
        if (!visited[i][size - 1])
        {
            reachable[i][size - 1] = true;
            q.push({size - 1, i});
        }
    }
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (in_bounds(nx, ny, size) && !visited[ny][nx] && !reachable[ny][nx])
            {
                reachable[ny][nx] = true;
                q.push({nx, ny});
            }
        }
    }
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (!visited[y][x] && !reachable[y][x])
                visited[y][x] = true;
        }
    }
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    int start_x = -1, start_y = -1;
    int y = 0;
    const int offset = 100;
    const int grid_size = 200;
    vector<vector<bool>> visited(grid_size, vector<bool>(grid_size, false));
    vector<pair<int, int>> bones;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        for (int x = 0; x < line.length(); x++)
        {
            if (line[x] == '@')
            {
                start_x = x;
                start_y = y;
            }
            else if (line[x] == '#')
            {
                int bone_x = x + offset;
                int bone_y = y + offset;
                visited[bone_y][bone_x] = true;
                bones.push_back({bone_x, bone_y});
            }
        }
        y++;
    }
    int curr_x = start_x + offset;
    int curr_y = start_y + offset;
    visited[curr_y][curr_x] = true;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    int seq[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
    int seq_idx = 0;
    int steps = 0;
    bool all_surrounded = false;
    while (!all_surrounded)
    {
        while (true)
        {
            int dir = seq[seq_idx];
            seq_idx = (seq_idx + 1) % 12;
            int nx = curr_x + dx[dir];
            int ny = curr_y + dy[dir];
            if (!visited[ny][nx])
            {
                curr_x = nx;
                curr_y = ny;
                visited[ny][nx] = true;
                steps++;
                fill(visited, grid_size);
                break;
            }
        }
        all_surrounded = true;
        for (int b = 0; b < bones.size(); b++)
        {
            int bx = bones[b].first;
            int by = bones[b].second;
            for (int i = 0; i < 4; i++)
            {
                int nx = bx + dx[i];
                int ny = by + dy[i];
                if (!visited[ny][nx])
                {
                    all_surrounded = false;
                    break;
                }
            }
            if (!all_surrounded)
                break;
        }
    }
    output_file << steps << endl;
    return 0;
}