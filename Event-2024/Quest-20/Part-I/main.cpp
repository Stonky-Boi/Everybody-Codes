#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int get_cost(char c)
{
    if (c == '+')
        return 1;
    if (c == '-')
        return -2;
    return -1; // for '.' and 'S'
}

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
    // Directions: 0 = North, 1 = East, 2 = South, 3 = West
    vector<vector<vector<int>>> curr_dp(rows, vector<vector<int>>(columns, vector<int>(4, INF)));
    for (int d = 0; d < 4; d++)
        curr_dp[start_row][start_column][d] = 1000;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    for (int t = 1; t <= 100; t++)
    {
        vector<vector<vector<int>>> next_dp(rows, vector<vector<int>>(columns, vector<int>(4, INF)));
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < columns; c++)
            {
                for (int d = 0; d < 4; d++)
                {
                    if (curr_dp[r][c][d] == INF)
                        continue;
                    int turns[] = {-1, 0, 1};
                    for (int i = 0; i < 3; i++)
                    {
                        int next_direction = (d + turns[i] + 4) % 4;
                        int nx = r + dx[next_direction];
                        int ny = c + dy[next_direction];
                        if (nx >= 0 && nx < rows && ny >= 0 && ny < columns && grid[nx][ny] != '#')
                        {
                            int cost = get_cost(grid[nx][ny]);
                            if (curr_dp[r][c][d] + cost > next_dp[nx][ny][next_direction])
                                next_dp[nx][ny][next_direction] = curr_dp[r][c][d] + cost;
                        }
                    }
                }
            }
        }
        curr_dp = next_dp;
    }
    int max_altitude = INF;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            for (int d = 0; d < 4; d++)
            {
                if (curr_dp[r][c][d] > max_altitude)
                    max_altitude = curr_dp[r][c][d];
            }
        }
    }
    output_file << max_altitude;
    return 0;
}