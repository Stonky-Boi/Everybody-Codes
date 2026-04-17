#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

int get_drop(char c)
{
    if (c == '+')
        return -1;
    if (c == '-')
        return 2;
    return 1; // for '.', 'S', 'A', 'B' and 'C'
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
    int H = grid.size();
    int W = grid[0].size();
    int start_column = -1;
    for (int c = 0; c < W; c++)
    {
        if (grid[0][c] == 'S')
        {
            start_column = c;
            break;
        }
    }
    const int MAX_R = 15000;
    const int INF = 1e9;
    // Track the optimal Net Cost and Required Initial Altitude to survive the path
    vector<vector<vector<int>>> best_nc(MAX_R, vector<vector<int>>(W, vector<int>(4, INF)));
    vector<vector<vector<int>>> best_r(MAX_R, vector<vector<int>>(W, vector<int>(4, INF)));
    // Priority Queue stores: {Net Cost, Required Altitude, Row, Col, Direction}
    priority_queue<tuple<int, int, int, int, int>, vector<tuple<int, int, int, int, int>>, greater<>> pq;
    for (int d = 0; d < 4; d++)
    {
        best_nc[0][start_column][d] = 0;
        best_r[0][start_column][d] = 0;
        pq.push({0, 0, 0, start_column, d});
    }
    int dx[] = {-1, 0, 1, 0}; // North, East, South, West
    int dy[] = {0, 1, 0, -1};
    while (!pq.empty())
    {
        auto [nc, req, r, c, d] = pq.top();
        pq.pop();
        if (nc > best_nc[r][c][d] || (nc == best_nc[r][c][d] && req > best_r[r][c][d]))
            continue;
        for (int turn : {-1, 0, 1})
        {
            int nd = (d + turn + 4) % 4;
            int nx = r + dx[nd];
            int ny = c + dy[nd];
            if (nx >= 0 && nx < MAX_R && ny >= 0 && ny < W && grid[nx % H][ny] != '#')
            {
                int drop = get_drop(grid[nx % H][ny]);
                int new_nc = nc + drop;
                int new_req = max(req, nc + 1);
                if (new_nc < best_nc[nx][ny][nd] || (new_nc == best_nc[nx][ny][nd] && new_req < best_r[nx][ny][nd]))
                {
                    best_nc[nx][ny][nd] = new_nc;
                    best_r[nx][ny][nd] = new_req;
                    pq.push({new_nc, new_req, nx, ny, nd});
                }
            }
        }
    }
    // Collapse into the minimum required altitude for each row
    vector<int> required(MAX_R, INF);
    for (int r = 0; r < MAX_R; r++)
    {
        for (int c = 0; c < W; c++)
        {
            for (int d = 0; d < 4; d++)
                required[r] = min(required[r], best_r[r][c][d]);
        }
    }
    // Lookup maximum row reachable given a specific starting altitude 'A'
    vector<int> value(1500);
    for (int A = 0; A < 1500; A++)
    {
        int max_r = 0;
        for (int r = 0; r < MAX_R; r++)
        {
            if (required[r] <= A)
                max_r = r;
        }
        value[A] = max_r;
    }
    int period_A = -1;
    int delta_row = -1;
    for (int T = 1; T <= 500; T++)
    {
        bool possible = true;
        int diff = value[1200] - value[1200 - T];
        for (int A = 1200; A >= 1000; --A)
        {
            if (value[A] - value[A - T] != diff)
            {
                possible = false;
                break;
            }
        }
        if (possible)
        {
            period_A = T;
            delta_row = diff;
            break;
        }
    }
    long long A_target = 384400;
    long long max_distance = 0;
    if (period_A != -1)
    {
        long long k = (A_target - 1000) / period_A;
        long long A_base = A_target - k * period_A;
        max_distance = value[A_base] + k * (long long)delta_row;
    }
    else
        max_distance = value[A_target];
    output_file << max_distance;
    return 0;
}