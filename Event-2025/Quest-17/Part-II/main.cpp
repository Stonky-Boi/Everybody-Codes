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
    int max_destruction = 0;
    int best_radius = 0;
    int curr_radius = 1;
    int rows = grid.size();
    int columns = grid[0].size();
    while (true)
    {
        int curr_destruction = 0;
        bool reached_edge = false;
        int lower_bound = (curr_radius - 1) * (curr_radius - 1);
        int upper_bound = curr_radius * curr_radius;
        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                if (row == volcano_row && column == volcano_column)
                    continue;
                int row_diff = row - volcano_row;
                int column_diff = column - volcano_column;
                int distance = (row_diff * row_diff) + (column_diff * column_diff);
                if (distance > lower_bound && distance <= upper_bound)
                {
                    curr_destruction += (grid[row][column] - '0');
                    if (row == 0 || row == rows - 1 || column == 0 || column == columns - 1)
                        reached_edge = true;
                }
            }
        }
        if (curr_destruction > max_destruction)
        {
            max_destruction = curr_destruction;
            best_radius = curr_radius;
        }
        if (reached_edge)
            break;
        curr_radius++;
    }
    int result = max_destruction * best_radius;
    output_file << result << endl;
    return 0;
}