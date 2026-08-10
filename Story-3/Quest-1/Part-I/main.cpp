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
    int green_sum = 0;
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
        if (components.size() >= 3)
        {
            int red = decode(components[0]);
            int green = decode(components[1]);
            int blue = decode(components[2]);
            if (green > red && green > blue)
                green_sum += id;
        }
    }
    output_file << green_sum << endl;
    return 0;
}