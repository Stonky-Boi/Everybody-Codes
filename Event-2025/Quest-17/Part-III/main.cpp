#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct state
{
    int cost;
    int row;
    int column;
    int winding;

    bool operator>(const state &other) const
    {
        if (cost != other.cost)
            return cost > other.cost;
        if (row != other.row)
            return row > other.row;
        if (column != other.column)
            return column > other.column;
        return winding > other.winding;
    }
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    string line;
    int volcano_row = -1;
    int volcano_column = -1;
    int start_row = -1;
    int start_column = -1;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int r = grid.size();
        grid.push_back(line);
        for (int c = 0; c < line.length(); c++)
        {
            if (line[c] == '@')
            {
                volcano_row = r;
                volcano_column = c;
            }
            else if (line[c] == 'S')
            {
                start_row = r;
                start_column = c;
            }
        }
    }
    int rows = grid.size();
    int columns = grid[0].size();
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    int min_time = -1;
    for (int assumed_r = 0; assumed_r <= 100; assumed_r++)
    {
        int radius_squared = assumed_r * assumed_r;
        int sr_diff = start_row - volcano_row;
        int sc_diff = start_column - volcano_column;
        if ((sr_diff * sr_diff) + (sc_diff * sc_diff) <= radius_squared)
            continue;
        vector<vector<vector<int>>> min_cost(rows, vector<vector<int>>(columns, vector<int>(5, -1)));
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push({0, start_row, start_column, 0});
        min_cost[start_row][start_column][2] = 0;
        int best_time = -1;
        while (!pq.empty())
        {
            state curr = pq.top();
            pq.pop();
            int curr_cost = curr.cost;
            int r = curr.row;
            int c = curr.column;
            int winding = curr.winding;
            if (r == start_row && c == start_column && (winding == 1 || winding == -1))
            {
                best_time = curr_cost;
                break;
            }
            if (curr_cost > min_cost[r][c][winding + 2])
                continue;
            for (int i = 0; i < 4; i++)
            {
                int nr = r + dy[i];
                int nc = c + dx[i];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < columns)
                {
                    int row_diff = nr - volcano_row;
                    int column_diff = nc - volcano_column;
                    if ((row_diff * row_diff) + (column_diff * column_diff) <= radius_squared)
                        continue;
                    int next_winding = winding;
                    if (r < volcano_row && nr < volcano_row)
                    {
                        if (c == volcano_column && nc == volcano_column + 1)
                            next_winding++;
                        else if (c == volcano_column + 1 && nc == volcano_column)
                            next_winding--;
                    }
                    if (next_winding < -2 || next_winding > 2)
                        continue;
                    int step_cost = 0;
                    if (grid[nr][nc] != 'S' && grid[nr][nc] != '@')
                        step_cost = grid[nr][nc] - '0';
                    int next_cost = curr_cost + step_cost;
                    if (min_cost[nr][nc][next_winding + 2] == -1 || next_cost < min_cost[nr][nc][next_winding + 2])
                    {
                        min_cost[nr][nc][next_winding + 2] = next_cost;
                        pq.push({next_cost, nr, nc, next_winding});
                    }
                }
            }
        }
        if (best_time != -1)
        {
            int actual_r = best_time / 30;
            if (actual_r <= assumed_r)
            {
                if (min_time == -1 || best_time < min_time)
                    min_time = best_time;
            }
        }
    }
    int final_radius = min_time / 30;
    output_file << min_time * final_radius << endl;
    return 0;
}