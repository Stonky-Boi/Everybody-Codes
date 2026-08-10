#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct sheep
{
    int row;
    int column;
};

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
    vector<vector<bool>> hideout(rows, vector<bool>(columns, false));
    vector<sheep> active_sheep;
    int start_row = -1;
    int start_column = -1;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == '#')
                hideout[r][c] = true;
            else if (grid[r][c] == 'S')
                active_sheep.push_back({r, c});
            else if (grid[r][c] == 'D')
            {
                start_row = r;
                start_column = c;
            }
        }
    }
    vector<vector<bool>> curr_reach(rows, vector<bool>(columns, false));
    curr_reach[start_row][start_column] = true;
    int row_moves[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int column_moves[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    int eaten_count = 0;
    int total_rounds = 20;
    for (int round = 1; round <= total_rounds; round++)
    {
        vector<vector<bool>> next_reach(rows, vector<bool>(columns, false));
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < columns; c++)
            {
                if (curr_reach[r][c])
                {
                    for (int m = 0; m < 8; m++)
                    {
                        int next_r = r + row_moves[m];
                        int next_c = c + column_moves[m];
                        if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < columns)
                            next_reach[next_r][next_c] = true;
                    }
                }
            }
        }
        curr_reach = next_reach;
        vector<sheep> surviving_sheep;
        for (const sheep &s : active_sheep)
        {
            if (curr_reach[s.row][s.column] && !hideout[s.row][s.column])
                eaten_count++;
            else
                surviving_sheep.push_back(s);
        }
        active_sheep = surviving_sheep;
        surviving_sheep.clear();
        for (sheep &s : active_sheep)
        {
            s.row += 1;
            if (s.row < rows)
            {
                if (curr_reach[s.row][s.column] && !hideout[s.row][s.column])
                    eaten_count++;
                else
                    surviving_sheep.push_back(s);
            }
        }
        active_sheep = surviving_sheep;
    }
    output_file << eaten_count << endl;
    return 0;
}