#include <iostream>
#include <vector>
#include <fstream>
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
    int ground = rows - 1;
    vector<pair<pair<int, int>, int>> targets;
    for (int r = 0; r < rows - 1; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == 'T')
            {
                int y = ground - r - 1;
                targets.push_back({{c - 1, y}, 1});
            }
            else if (grid[r][c] == 'H')
            {
                int y = ground - r - 1;
                targets.push_back({{c - 1, y}, 2});
            }
        }
    }
    long long ranking = 0;
    for (const auto &[t, health] : targets)
    {
        auto [tx, ty] = t;
        long long min_cost = 1e18;
        for (int power = 1; power <= tx + 10; power++)
        {
            for (char segment : {'A', 'B', 'C'})
            {
                if (distance(segment, power, tx) == ty)
                {
                    long long cost = power * (segment - 'A' + 1);
                    if (cost < min_cost)
                        min_cost = cost;
                }
            }
        }
        if (min_cost != 1e18)
            ranking += min_cost * health;
    }
    output_file << ranking;
    return 0;
}