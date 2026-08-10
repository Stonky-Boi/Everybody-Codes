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
    int volcano_row = -1;
    int volcano_column = -1;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        grid.push_back(line);
        int position = line.find('@');
        if (position != string::npos)
        {
            volcano_row = grid.size() - 1;
            volcano_column = position;
        }
    }
    int sum = 0;
    int radius = 10;
    int radius_squared = radius * radius;
    for (int row = 0; row < grid.size(); row++)
    {
        for (int column = 0; column < grid[row].size(); column++)
        {
            if (row == volcano_row && column == volcano_column)
                continue;
            int row_diff = row - volcano_row;
            int column_diff = column - volcano_column;
            if ((row_diff * row_diff) + (column_diff * column_diff) <= radius_squared)
                sum += (grid[row][column] - '0');
        }
    }
    output_file << sum << endl;
    return 0;
}