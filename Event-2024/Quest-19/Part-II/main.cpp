#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string key;
    getline(input_file, key);
    string line;
    getline(input_file, line); // skip empty line
    vector<string> grid;
    while (getline(input_file, line))
    {
        if (!line.empty())
            grid.push_back(line);
    }
    int rows = grid.size();
    int columns = grid[0].size();
    int key_length = key.length();
    for (int round = 0; round < 100; round++)
    {
        int key_index = 0;
        for (int r = 1; r < rows - 1; r++)
        {
            for (int c = 1; c < columns - 1; c++)
            {
                char operation = key[key_index % key_length];
                char top_left = grid[r - 1][c - 1];
                char top_mid = grid[r - 1][c];
                char top_right = grid[r - 1][c + 1];
                char right = grid[r][c + 1];
                char bottom_right = grid[r + 1][c + 1];
                char bottom_mid = grid[r + 1][c];
                char bottom_left = grid[r + 1][c - 1];
                char left = grid[r][c - 1];
                if (operation == 'R')
                {
                    grid[r - 1][c - 1] = left;
                    grid[r - 1][c] = top_left;
                    grid[r - 1][c + 1] = top_mid;
                    grid[r][c + 1] = top_right;
                    grid[r + 1][c + 1] = right;
                    grid[r + 1][c] = bottom_right;
                    grid[r + 1][c - 1] = bottom_mid;
                    grid[r][c - 1] = bottom_left;
                }
                else if (operation == 'L')
                {
                    grid[r - 1][c - 1] = top_mid;
                    grid[r - 1][c] = top_right;
                    grid[r - 1][c + 1] = right;
                    grid[r][c + 1] = bottom_right;
                    grid[r + 1][c + 1] = bottom_mid;
                    grid[r + 1][c] = bottom_left;
                    grid[r + 1][c - 1] = left;
                    grid[r][c - 1] = top_left;
                }
                key_index++;
            }
        }
    }
    string message = "";
    bool reading_message = false;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (!reading_message)
            {
                if (grid[r][c] == '>')
                    reading_message = true;
            }
            else
            {
                if (grid[r][c] == '<')
                {
                    output_file << message;
                    return 0;
                }
                message += grid[r][c];
            }
        }
    }
    return 0;
}