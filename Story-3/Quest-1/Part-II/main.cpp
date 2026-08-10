#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int decode(const string &color)
{
    int value = 0;
    for (char c : color)
    {
        value <<= 1;
        if (c >= 'A' && c <= 'Z')
            value |= 1;
    }
    return value;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    int max_shine = -1;
    int min_sum = -1;
    int best_scale = -1;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int colon = line.find(':');
        if (colon == string::npos)
            continue;
        int id = stoi(line.substr(0, colon));
        string data = line.substr(colon + 1);
        int first_char = data.find_first_not_of(' ');
        if (first_char != string::npos)
            data = data.substr(first_char);
        vector<string> components;
        int position = 0;
        while (position < data.length())
        {
            int space = data.find(' ', position);
            if (space == string::npos)
            {
                components.push_back(data.substr(position));
                break;
            }
            if (space > position)
                components.push_back(data.substr(position, space - position));
            position = space + 1;
        }
        if (components.size() >= 4)
        {
            int red = decode(components[0]);
            int green = decode(components[1]);
            int blue = decode(components[2]);
            int shine = decode(components[3]);
            int color_sum = red + green + blue;
            if (shine > max_shine)
            {
                max_shine = shine;
                min_sum = color_sum;
                best_scale = id;
            }
            else if (shine == max_shine)
            {
                if (min_sum == -1 || color_sum < min_sum)
                {
                    min_sum = color_sum;
                    best_scale = id;
                }
            }
        }
    }
    output_file << best_scale << std::endl;
    return 0;
}