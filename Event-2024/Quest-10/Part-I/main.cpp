#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    string line;
    while (input_file >> line)
        grid.push_back(line);
    string result = "";
    for (int r = 2; r <= 5; r++)
    {
        for (int c = 2; c <= 5; c++)
        {
            string row_chars = "";
            row_chars += grid[r][0];
            row_chars += grid[r][1];
            row_chars += grid[r][6];
            row_chars += grid[r][7];
            string column_chars = "";
            column_chars += grid[0][c];
            column_chars += grid[1][c];
            column_chars += grid[6][c];
            column_chars += grid[7][c];
            char match = ' ';
            for (char rc : row_chars)
            {
                bool found = false;
                for (char cc : column_chars)
                {
                    if (rc == cc)
                    {
                        match = rc;
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
            }
            result += match;
        }
    }
    output_file << result;
    return 0;
}