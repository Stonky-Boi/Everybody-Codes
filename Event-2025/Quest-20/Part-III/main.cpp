#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

void rotate(int r, int rel_c, int rows, int &out_r, int &out_rel_c)
{
    if (rel_c % 2 == 0)
    {
        int x = r;
        int y = rel_c / 2;
        int z = rows - 1 - x - y;
        out_r = y;
        out_rel_c = z * 2;
    }
    else
    {
        int x = r;
        int y = (rel_c - 1) / 2;
        int z = rows - 2 - x - y;
        out_r = y;
        out_rel_c = z * 2 + 1;
    }
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid0;
    string line;
    int start_r = -1, start_c = -1;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int r = grid0.size();
        for (int c = 0; c < line.length(); c++)
        {
            if (line[c] == 'S')
            {
                start_r = r;
                start_c = c;
            }
        }
        grid0.push_back(line);
    }
    int rows = grid0.size();
    int columns = grid0[0].size();
    vector<string> grid1 = grid0;
    vector<string> grid2 = grid0;
    for (int r = 0; r < rows; r++)
    {
        int valid_count = 2 * (rows - r) - 1;
        for (int rel_c = 0; rel_c < valid_count; rel_c++)
        {
            int c = r + rel_c;
            int r1, rel_c1;
            rotate(r, rel_c, rows, r1, rel_c1);
            grid1[r1][r1 + rel_c1] = grid0[r][c];
            int r2, rel_c2;
            rotate(r1, rel_c1, rows, r2, rel_c2);
            grid2[r2][r2 + rel_c2] = grid0[r][c];
        }
    }
    vector<vector<string>> grids;
    grids.push_back(grid0);
    grids.push_back(grid1);
    grids.push_back(grid2);
    queue<tuple<int, int, int>> q;
    vector<vector<vector<int>>> distance(3, vector<vector<int>>(rows, vector<int>(columns, -1)));
    q.push({0, start_r, start_c});
    distance[0][start_r][start_c] = 0;
    while (!q.empty())
    {
        auto [d, r, c] = q.front();
        q.pop();
        int state = d % 3;
        int next_state = (d + 1) % 3;
        int dr[] = {0, 0, 0, 0};
        int dc[] = {-1, 1, 0, 0};
        int rel_c = c - r;
        if (rel_c % 2 == 0)
            dr[3] = -1;
        else
            dr[3] = 1;
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < rows && nc >= nr && nc < nr + 2 * (rows - nr) - 1)
            {
                char next_ch = grids[next_state][nr][nc];
                if (next_ch != '#' && next_ch != '.')
                {
                    if (distance[next_state][nr][nc] == -1)
                    {
                        if (next_ch == 'E')
                        {
                            output_file << d + 1 << endl;
                            return 0;
                        }
                        distance[next_state][nr][nc] = d + 1;
                        q.push({d + 1, nr, nc});
                    }
                }
            }
        }
    }
    return 0;
}