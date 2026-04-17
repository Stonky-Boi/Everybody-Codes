#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

int get_cost(char c)
{
    if (c == '+')
        return 1;
    if (c == '-')
        return -2;
    return -1; // for '.', 'S', 'A', 'B' and 'C'
}

struct state
{
    int row;
    int column;
    int direction;
    int stage;
    int time;
    int altitude;
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
    int start_row = -1;
    int start_column = -1;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == 'S')
            {
                start_row = r;
                start_column = c;
            }
        }
    }
    const int INF = -1000000000;
    // 4D DP table: [row][column][direction][checkpoint_stage] tracking the maximum altitude
    // Stages: 0 (Need A), 1 (Need B), 2 (Need C), 3 (Need S to finish)
    vector<vector<vector<vector<int>>>> max_alt(rows, vector<vector<vector<int>>>(columns, vector<vector<int>>(4, vector<int>(4, INF))));
    queue<state> q;
    for (int d = 0; d < 4; d++)
    {
        max_alt[start_row][start_column][d][0] = 10000;
        q.push({start_row, start_column, d, 0, 0, 10000});
    }
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    int shortest_time = -1;
    while (!q.empty())
    {
        state curr = q.front();
        q.pop();
        int turns[] = {-1, 0, 1};
        for (int i = 0; i < 3; i++)
        {
            int next_direction = (curr.direction + turns[i] + 4) % 4;
            int nx = curr.row + dx[next_direction];
            int ny = curr.column + dy[next_direction];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < columns && grid[nx][ny] != '#')
            {
                int new_altitude = curr.altitude + get_cost(grid[nx][ny]);
                int new_stage = curr.stage;
                char cell = grid[nx][ny];
                if (new_stage == 0 && cell == 'A')
                    new_stage = 1;
                else if (new_stage == 1 && cell == 'B')
                    new_stage = 2;
                else if (new_stage == 2 && cell == 'C')
                    new_stage = 3;
                if (new_stage == 3 && cell == 'S')
                {
                    if (new_altitude >= 10000)
                    {
                        shortest_time = curr.time + 1;
                        output_file << shortest_time;
                        return 0;
                    }
                }
                if (new_altitude > max_alt[nx][ny][next_direction][new_stage])
                {
                    max_alt[nx][ny][next_direction][new_stage] = new_altitude;
                    q.push({nx, ny, next_direction, new_stage, curr.time + 1, new_altitude});
                }
            }
        }
    }
    return 0;
}