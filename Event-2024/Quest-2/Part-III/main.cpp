#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string words_line;
    getline(input_file, words_line);
    words_line = words_line.substr(6);
    vector<string> words;
    string current_word = "";
    for (char c : words_line)
    {
        if (c == ',')
        {
            words.push_back(current_word);
            current_word = "";
        }
        else
            current_word += c;
    }
    if (!current_word.empty())
        words.push_back(current_word);
    vector<string> grid;
    string text_line;
    while (getline(input_file, text_line))
    {
        if (text_line.empty())
            continue;
        grid.push_back(text_line);
    }
    int r_size = grid.size();
    int c_size = grid[0].size();
    vector<vector<bool>> is_runic(r_size, vector<bool>(c_size, false));
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    for (string w : words)
    {
        int length = w.length();
        for (int r = 0; r < r_size; r++)
        {
            for (int c = 0; c < c_size; c++)
            {
                for (int d = 0; d < 4; d++)
                {
                    bool match = true;
                    for (int k = 0; k < length; k++)
                    {
                        int nr = r + k * dr[d];
                        int nc = c + k * dc[d];
                        if (nr < 0 || nr >= r_size)
                        {
                            match = false;
                            break;
                        }
                        nc = nc % c_size;
                        if (nc < 0)
                            nc += c_size;
                        if (grid[nr][nc] != w[k])
                        {
                            match = false;
                            break;
                        }
                    }
                    if (match)
                    {
                        for (int k = 0; k < length; k++)
                        {
                            int nr = r + k * dr[d];
                            int nc = c + k * dc[d];
                            nc = nc % c_size;
                            if (nc < 0)
                                nc += c_size;
                            is_runic[nr][nc] = true;
                        }
                    }
                }
            }
        }
    }
    long long total_scales = 0;
    for (int r = 0; r < r_size; r++)
    {
        for (int c = 0; c < c_size; c++)
        {
            if (is_runic[r][c])
                total_scales++;
        }
    }
    output_file << total_scales;
    return 0;
}