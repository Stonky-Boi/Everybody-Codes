#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    string line;
    int start_r = -1;
    int start_c = -1;
    int end_r = -1;
    int end_c = -1;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int r = grid.size();
        for (int c = 0; c < line.length(); c++)
        {
            if (line[c] == 'S')
            {
                start_r = r;
                start_c = c;
            }
            else if (line[c] == 'E')
            {
                end_r = r;
                end_c = c;
            }
        }
        grid.push_back(line);
    }
    int rows = grid.size();
    int columns = grid[0].size();
    vector<vector<int>> distance(rows, vector<int>(columns, -1));
    queue<pair<int, int>> q;
    q.push({start_r, start_c});
    distance[start_r][start_c] = 0;
    while (!q.empty())
    {
        auto [r, c] = q.front();
        q.pop();
        if (r == end_r && c == end_c)
        {
            output_file << distance[r][c] << endl;
            return 0;
        }
        int dr[] = {0, 0, 0};
        int dc[] = {-1, 1, 0};
        if ((r + c) % 2 == 0)
            dr[2] = -1;
        else
            dr[2] = 1;
        for (int i = 0; i < 3; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < grid[nr].length())
            {
                char ch = grid[nr][nc];
                if ((ch == 'T' || ch == 'E' || ch == 'S') && distance[nr][nc] == -1)
                {
                    distance[nr][nc] = distance[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
    return 0;
}