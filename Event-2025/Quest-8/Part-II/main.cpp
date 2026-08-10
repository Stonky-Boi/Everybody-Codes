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
    getline(input_file, line);
    vector<int> sequence;
    int start = 0;
    int comma = line.find(',');
    while (comma != string::npos)
    {
        sequence.push_back(stoi(line.substr(start, comma - start)));
        start = comma + 1;
        comma = line.find(',', start);
    }
    if (start < line.length())
        sequence.push_back(stoi(line.substr(start)));
    int total_knots = 0;
    vector<pair<int, int>> drawn_segments;
    for (int i = 1; i < sequence.size(); i++)
    {
        int u = min(sequence[i - 1], sequence[i]);
        int v = max(sequence[i - 1], sequence[i]);
        for (const auto &[x, y] : drawn_segments)
        {
            if ((u < x && x < v && v < y) || (x < u && u < y && y < v))
                total_knots++;
        }
        drawn_segments.push_back({u, v});
    }
    output_file << total_knots << endl;
    return 0;
}