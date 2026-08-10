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
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
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
            if (grid[r][c] == 'D')
            {
                start_row = r;
                start_column = c;
                break;
            }
        }
        if (start_row != -1)
            break;
    }
    vector<vector<int>> distance(rows, vector<int>(columns, -1));
    queue<pair<int, int>> q;
    q.push({start_row, start_column});
    distance[start_row][start_column] = 0;
    int row_moves[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int column_moves[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    int sheep_count = 0;
    while (!q.empty())
    {
        auto [curr_row, curr_column] = q.front();
        q.pop();
        if (distance[curr_row][curr_column] <= 4)
        {
            if (grid[curr_row][curr_column] == 'S')
                sheep_count++;
        }
        if (distance[curr_row][curr_column] == 4)
            continue;
        for (int i = 0; i < 8; i++)
        {
            int next_row = curr_row + row_moves[i];
            int next_column = curr_column + column_moves[i];
            if (next_row >= 0 && next_row < rows && next_column >= 0 && next_column < columns)
            {
                if (distance[next_row][next_column] == -1)
                {
                    distance[next_row][next_column] = distance[curr_row][curr_column] + 1;
                    q.push({next_row, next_column});
                }
            }
        }
    }
    output_file << sheep_count << endl;
    return 0;
}