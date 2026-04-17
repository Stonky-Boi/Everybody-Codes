#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

int distance(char segment, int power, int x)
{
    int y = segment - 'A';
    if (x <= power)
        return y + x;
    if (x <= 2 * power)
        return y + power;
    return y + power - (x - 2 * power);
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
    int ground_row = rows - 1;
    vector<pair<int, int>> targets;
    for (int r = 0; r < rows - 1; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == 'T')
            {
                int y = ground_row - r - 1;
                targets.push_back({c - 1, y});
            }
        }
    }
    long long ranking = 0;
    for (const auto &[tx, ty] : targets)
    {
        bool hit = false;
        for (int power = 1; power <= tx && !hit; power++)
        {
            for (char segment : {'C', 'B', 'A'})
            {
                int y = distance(segment, power, tx);
                if (y == ty)
                {
                    ranking += power * (segment - 'A' + 1);
                    hit = true;
                    break;
                }
            }
        }
    }
    output_file << ranking;
    return 0;
}