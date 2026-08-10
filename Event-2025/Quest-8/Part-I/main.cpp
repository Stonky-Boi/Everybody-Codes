#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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
    int center_crossings = 0;
    int nails = 32;
    int difference = nails / 2;
    for (int i = 0; i + 1 < sequence.size(); i++)
    {
        if (abs(sequence[i] - sequence[i + 1]) == difference)
            center_crossings++;
    }
    output_file << center_crossings << endl;
    return 0;
}