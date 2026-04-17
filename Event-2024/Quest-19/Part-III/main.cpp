#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<int> compose_permutations(const vector<int> &perm_a, const vector<int> &perm_b)
{
    int size = perm_a.size();
    vector<int> result(size);
    for (int i = 0; i < size; i++)
        result[i] = perm_a[perm_b[i]];
    return result;
}

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
    vector<vector<int>> p_grid(rows, vector<int>(columns));
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
            p_grid[r][c] = r * columns + c;
    }
    int key_index = 0;
    for (int r = 1; r < rows - 1; r++)
    {
        for (int c = 1; c < columns - 1; c++)
        {
            char operation = key[key_index % key_length];
            int top_left = p_grid[r - 1][c - 1];
            int top_mid = p_grid[r - 1][c];
            int top_right = p_grid[r - 1][c + 1];
            int right = p_grid[r][c + 1];
            int bottom_right = p_grid[r + 1][c + 1];
            int bottom_mid = p_grid[r + 1][c];
            int bottom_left = p_grid[r + 1][c - 1];
            int left = p_grid[r][c - 1];
            if (operation == 'R')
            {
                p_grid[r - 1][c - 1] = left;
                p_grid[r - 1][c] = top_left;
                p_grid[r - 1][c + 1] = top_mid;
                p_grid[r][c + 1] = top_right;
                p_grid[r + 1][c + 1] = right;
                p_grid[r + 1][c] = bottom_right;
                p_grid[r + 1][c - 1] = bottom_mid;
                p_grid[r][c - 1] = bottom_left;
            }
            else if (operation == 'L')
            {
                p_grid[r - 1][c - 1] = top_mid;
                p_grid[r - 1][c] = top_right;
                p_grid[r - 1][c + 1] = right;
                p_grid[r][c + 1] = bottom_right;
                p_grid[r + 1][c + 1] = bottom_mid;
                p_grid[r + 1][c] = bottom_left;
                p_grid[r + 1][c - 1] = left;
                p_grid[r][c - 1] = top_left;
            }
            key_index++;
        }
    }
    int num_cells = rows * columns;
    vector<int> base_permutation(num_cells);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
            base_permutation[r * columns + c] = p_grid[r][c];
    }
    vector<int> result_permutation(num_cells);
    for (int i = 0; i < num_cells; i++)
        result_permutation[i] = i;
    long long rounds = 1048576000LL;
    while (rounds > 0)
    {
        if (rounds % 2 == 1)
            result_permutation = compose_permutations(result_permutation, base_permutation);
        base_permutation = compose_permutations(base_permutation, base_permutation);
        rounds /= 2;
    }
    string original_chars = "";
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
            original_chars += grid[r][c];
    }
    string final_chars = original_chars;
    for (int i = 0; i < num_cells; i++)
        final_chars[i] = original_chars[result_permutation[i]];
    string message = "";
    bool reading_message = false;
    for (int i = 0; i < num_cells; i++)
    {
        char curr_chars = final_chars[i];
        if (!reading_message)
        {
            if (curr_chars == '>')
                reading_message = true;
        }
        else
        {
            if (curr_chars == '<')
            {
                output_file << message;
                return 0;
            }
            message += curr_chars;
        }
    }
    return 0;
}