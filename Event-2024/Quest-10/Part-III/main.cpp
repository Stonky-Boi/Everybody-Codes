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
    while (getline(input_file, line))
    {
        if (!line.empty())
            grid.push_back(line);
    }
    int H = grid.size();
    int W = grid[0].length();
    vector<pair<int, int>> todo;
    for (int y = 0; y + 8 <= H; y += 6)
        for (int x = 0; x + 8 <= W; x += 6)
            todo.push_back({x, y});
    long long current_total = 0;
    bool changed = true;
    while (changed)
    {
        changed = false;
        vector<pair<int, int>> next_todo;
        for (const auto &[cx, cy] : todo)
        {
            bool is_valid = true;
            int global_seen = 0;
            for (int y = 2; y <= 5; y++)
            {
                int row_mask = 0;
                for (int i : {0, 1, 6, 7})
                {
                    char c = grid[cy + y][cx + i];
                    if (c >= 'A' && c <= 'Z')
                    {
                        if (row_mask & (1 << (c - 'A')))
                            is_valid = false;
                        row_mask |= (1 << (c - 'A'));
                        global_seen |= (1 << (c - 'A'));
                    }
                }
            }
            for (int x = 2; x <= 5; x++)
            {
                int col_mask = 0;
                for (int i : {0, 1, 6, 7})
                {
                    char c = grid[cy + i][cx + x];
                    if (c >= 'A' && c <= 'Z')
                    {
                        if (col_mask & (1 << (c - 'A')))
                            is_valid = false;
                        col_mask |= (1 << (c - 'A'));
                        global_seen |= (1 << (c - 'A'));
                    }
                }
            }
            if (!is_valid)
            {
                next_todo.push_back({cx, cy});
                continue;
            }
            int u_count = 0;
            for (int i = 0; i < 26; i++)
            {
                if (global_seen & (1 << i))
                    u_count++;
            }
            if (u_count != 16)
            {
                next_todo.push_back({cx, cy});
                continue;
            }
            for (int y = 2; y <= 5; y++)
            {
                for (int x = 2; x <= 5; x++)
                {
                    if (grid[cy + y][cx + x] != '.')
                        continue;
                    int row_mask = 0, column_mask = 0;
                    for (int i = 0; i < 8; i++)
                    {
                        char rc = grid[cy + y][cx + i];
                        if (rc >= 'A' && rc <= 'Z')
                            row_mask |= (1 << (rc - 'A'));
                        char cc = grid[cy + i][cx + x];
                        if (cc >= 'A' && cc <= 'Z')
                            column_mask |= (1 << (cc - 'A'));
                    }
                    int unique_intersection = row_mask & column_mask;
                    if (unique_intersection != 0 && (unique_intersection & (unique_intersection - 1)) == 0)
                    {
                        int bit = 0;
                        while ((unique_intersection & (1 << bit)) == 0)
                            bit++;
                        grid[cy + y][cx + x] = static_cast<char>('A' + bit);
                        changed = true;
                    }
                }
            }
            long long power = 0;
            bool is_solved = true;
            for (int y = 2; y <= 5; y++)
            {
                for (int x = 2; x <= 5; x++)
                {
                    char current = grid[cy + y][cx + x];
                    if (current >= 'A' && current <= 'Z')
                    {
                        power += (4LL * y + x - 9LL) * (current - 'A' + 1LL);
                        continue;
                    }
                    int unique_mask = 0;
                    int unknown_x = -1, unknown_y = -1;
                    for (int i = 0; i < 8; i++)
                    {
                        char cr = grid[cy + y][cx + i];
                        if (cr == '?')
                        {
                            unknown_x = cx + i;
                            unknown_y = cy + y;
                        }
                        else if (cr >= 'A' && cr <= 'Z')
                            unique_mask ^= (1 << (cr - 'A'));
                        char cc = grid[cy + i][cx + x];
                        if (cc == '?')
                        {
                            unknown_x = cx + x;
                            unknown_y = cy + i;
                        }
                        else if (cc >= 'A' && cc <= 'Z')
                            unique_mask ^= (1 << (cc - 'A'));
                    }
                    if (unique_mask != 0 && (unique_mask & (unique_mask - 1)) == 0)
                    {
                        int bit = 0;
                        while ((unique_mask & (1 << bit)) == 0)
                            bit++;
                        char ascii = static_cast<char>('A' + bit);
                        grid[cy + y][cx + x] = ascii;
                        if (unknown_x != -1 && unknown_y != -1)
                            grid[unknown_y][unknown_x] = ascii;
                        power += (4LL * y + x - 9LL) * (ascii - 'A' + 1LL);
                        changed = true;
                    }
                    else
                        is_solved = false;
                }
            }
            if (is_solved)
                current_total += power;
            else
                next_todo.push_back({cx, cy});
        }
        todo = next_todo;
    }
    output_file << current_total;
    return 0;
}