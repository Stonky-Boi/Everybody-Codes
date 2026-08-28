#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    int width = 0;
    int height = 0;
    string h_offset = "";
    string v_offset = "";
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (line.find("width=") == 0)
            width = stoi(line.substr(6));
        else if (line.find("height=") == 0)
            height = stoi(line.substr(7));
        else if (line.find("horizontal-offsets=") == 0)
            h_offset = line.substr(19);
        else if (line.find("vertical-offsets=") == 0)
            v_offset = line.substr(17);
    }
    int group_zero_count = 0;
    int group_one_count = 0;
    vector<int> prev_row_color(width, 0);
    vector<int> curr_row_color(width, 0);
    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            bool top_stitch = (c % 2 == (h_offset[r % h_offset.length()] - '0'));
            bool bottom_stitch = (c % 2 == (h_offset[(r + 1) % h_offset.length()] - '0'));
            bool left_stitch = (r % 2 == (v_offset[c % v_offset.length()] - '0'));
            bool right_stitch = (r % 2 == (v_offset[(c + 1) % v_offset.length()] - '0'));
            if (r == 0 && c == 0)
                curr_row_color[c] = 0;
            else if (c == 0)
            {
                if (top_stitch)
                    curr_row_color[c] = prev_row_color[c] ^ 1;
                else
                    curr_row_color[c] = prev_row_color[c];
            }
            else
            {
                if (left_stitch)
                    curr_row_color[c] = curr_row_color[c - 1] ^ 1;
                else
                    curr_row_color[c] = curr_row_color[c - 1];
            }
            if (top_stitch && bottom_stitch && left_stitch && right_stitch)
            {
                if (curr_row_color[c] == 0)
                    group_zero_count++;
                else
                    group_one_count++;
            }
        }
        prev_row_color = curr_row_color;
    }
    int larger_group = max(group_zero_count, group_one_count);
    output_file << larger_group << endl;
    return 0;
}