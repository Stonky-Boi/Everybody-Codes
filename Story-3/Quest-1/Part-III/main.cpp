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
    vector<int> group_counts(6, 0);
    vector<int> group_sums(6, 0);
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
            int dominant_color = -1;
            if (red > green && red > blue)
                dominant_color = 0;
            else if (green > red && green > blue)
                dominant_color = 1;
            else if (blue > red && blue > green)
                dominant_color = 2;
            int shine_category = -1;
            if (shine <= 30)
                shine_category = 0;
            else if (shine >= 33)
                shine_category = 1;
            if (dominant_color != -1 && shine_category != -1)
            {
                int group_index = dominant_color * 2 + shine_category;
                group_counts[group_index]++;
                group_sums[group_index] += id;
            }
        }
    }
    int max_count = -1;
    int best_sum = 0;
    for (int i = 0; i < 6; i++)
    {
        if (group_counts[i] > max_count)
        {
            max_count = group_counts[i];
            best_sum = group_sums[i];
        }
    }
    output_file << best_sum << endl;
    return 0;
}