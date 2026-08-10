#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    int start_x = -1, start_y = -1;
    int target_x = -1, target_y = -1;
    int y = 0;
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
                target_x = x;
                target_y = y;
            }
        }
        y++;
    }
    const int offset = 100;
    const int grid_size = 200;
    vector<vector<bool>> visited(grid_size, vector<bool>(grid_size, false));
    int curr_x = start_x;
    int curr_y = start_y;
    visited[curr_y + offset][curr_x + offset] = true;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    int next_dir = 0;
    int steps = 0;
    while (curr_x != target_x || curr_y != target_y)
    {
        for (int i = 0; i < 4; i++)
        {
            int dir = (next_dir + i) % 4;
            int nx = curr_x + dx[dir];
            int ny = curr_y + dy[dir];
            if (!visited[ny + offset][nx + offset])
            {
                curr_x = nx;
                curr_y = ny;
                visited[ny + offset][nx + offset] = true;
                next_dir = (dir + 1) % 4;
                steps++;
                break;
            }
        }
    }
    output_file << steps << endl;
    return 0;
}