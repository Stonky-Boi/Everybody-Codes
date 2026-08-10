#include <iostream>
#include <fstream>
#include <vector>
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
    int columns = grid[0].length();
    int pair_count = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == 'T')
            {
                if (c + 1 < columns && grid[r][c + 1] == 'T')
                    pair_count++;
                int relative_index = c - r;
                if (relative_index >= 0 && relative_index % 2 != 0)
                {
                    int next_r = r + 1;
                    if (next_r < rows && c < grid[next_r].length())
                    {
                        if (grid[next_r][c] == 'T')
                            pair_count++;
                    }
                }
            }
        }
    }
    output_file << pair_count << endl;
    return 0;
}