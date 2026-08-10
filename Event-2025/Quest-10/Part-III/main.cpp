#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

int rows, columns;
vector<string> grid;
vector<vector<bool>> hideout;
int start_dr, start_dc;
vector<int> initial_sheep;
map<long long, long long> memo;
map<long long, bool> visited;
int row_moves[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int column_moves[] = {-1, 1, -2, 2, -2, 2, -1, 1};

long long encode_state(int dr, int dc, int turn, const vector<int> &sheep)
{
    long long state = 0;
    state |= (long long)dr;
    state |= ((long long)dc << 5);
    state |= ((long long)turn << 10);
    int shift = 11;
    for (int i = 0; i < columns; i++)
    {
        state |= ((long long)sheep[i] << shift);
        shift += 5;
    }
    return state;
}

long long solve(int dr, int dc, int turn, vector<int> &sheep)
{
    bool all_eaten = true;
    for (int s : sheep)
    {
        if (s != 0)
        {
            all_eaten = false;
            break;
        }
    }
    if (all_eaten)
        return 1;
    long long state = encode_state(dr, dc, turn, sheep);
    if (visited[state])
        return 0;
    if (memo.count(state))
        return memo[state];
    visited[state] = true;
    long long total_ways = 0;
    if (turn == 0)
    {
        bool can_move = false;
        for (int c = 0; c < columns; c++)
        {
            int r = sheep[c];
            if (r == 0)
                continue;
            int nr = r + 1;
            if (nr <= rows && nr == dr && c == dc && !hideout[nr][c])
                continue;
            can_move = true;
            if (nr > rows)
                continue;
            sheep[c] = nr;
            total_ways += solve(dr, dc, 1, sheep);
            sheep[c] = r;
        }
        if (!can_move)
            total_ways = solve(dr, dc, 1, sheep);
    }
    else
    {
        for (int m = 0; m < 8; m++)
        {
            int nr = dr + row_moves[m];
            int nc = dc + column_moves[m];
            if (nr >= 1 && nr <= rows && nc >= 0 && nc < columns)
            {
                vector<int> next_sheep = sheep;
                for (int c = 0; c < columns; c++)
                {
                    if (next_sheep[c] == nr && c == nc && !hideout[nr][nc])
                        next_sheep[c] = 0;
                }
                total_ways += solve(nr, nc, 0, next_sheep);
            }
        }
    }
    visited[state] = false;
    return memo[state] = total_ways;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        grid.push_back(line);
    }
    rows = grid.size();
    columns = grid[0].size();
    hideout.assign(rows + 1, vector<bool>(columns, false));
    initial_sheep.assign(columns, 0);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            char ch = grid[r][c];
            if (ch == '#')
                hideout[r + 1][c] = true;
            else if (ch == 'S')
                initial_sheep[c] = r + 1;
            else if (ch == 'D')
            {
                start_dr = r + 1;
                start_dc = c;
            }
        }
    }
    long long count = solve(start_dr, start_dc, 0, initial_sheep);
    output_file << count << endl;
    return 0;
}