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
    int curr_x = 0;
    int lower_bound = 0;
    int upper_bound = 0;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        vector<int> values;
        int position = 0;
        while (position < line.length())
        {
            int comma = line.find(',', position);
            if (comma == string::npos)
                comma = line.length();
            string token = line.substr(position, comma - position);
            if (!token.empty())
                values.push_back(stoi(token));
            position = comma + 1;
        }
        if (values.size() >= 3)
        {
            int x = values[0];
            int y_start = values[1];
            int height = values[2];
            int dx = x - curr_x;
            int next_lower = lower_bound - dx;
            int next_upper = upper_bound + dx;
            lower_bound = max(next_lower, y_start);
            upper_bound = min(next_upper, y_start + height - 1);
            int parity_l = lower_bound % 2;
            if (parity_l < 0)
                parity_l += 2;
            if (parity_l != (x % 2))
                lower_bound++;
            int parity_r = upper_bound % 2;
            if (parity_r < 0)
                parity_r += 2;
            if (parity_r != (x % 2))
                upper_bound--;
            curr_x = x;
        }
    }
    int minimum_flaps = (curr_x + lower_bound) / 2;
    output_file << minimum_flaps << endl;
    return 0;
}