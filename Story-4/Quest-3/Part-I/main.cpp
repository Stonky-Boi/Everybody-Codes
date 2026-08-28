#include <iostream>
#include <fstream>
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
    int isolated_tiles = 0;
    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            bool top_stitch = (c % 2 == (h_offset[r % h_offset.length()] - '0'));
            bool bottom_stitch = (c % 2 == (h_offset[(r + 1) % h_offset.length()] - '0'));
            bool left_stitch = (r % 2 == (v_offset[c % v_offset.length()] - '0'));
            bool right_stitch = (r % 2 == (v_offset[(c + 1) % v_offset.length()] - '0'));
            if (top_stitch && bottom_stitch && left_stitch && right_stitch)
                isolated_tiles++;
        }
    }
    output_file << isolated_tiles << endl;
    return 0;
}