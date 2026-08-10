#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    vector<int> spell_numbers;
    int position = 0;
    while (position < line.length())
    {
        int comma = line.find(',', position);
        if (comma == string::npos)
            comma = line.length();
        string token = line.substr(position, comma - position);
        if (!token.empty())
            spell_numbers.push_back(stoi(token));
        position = comma + 1;
    }
    int blocks = 0;
    int length = 90;
    for (int s : spell_numbers)
    {
        if (s > 0)
            blocks += (length / s);
    }
    output_file << blocks << endl;
    return 0;
}