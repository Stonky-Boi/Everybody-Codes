#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    map<int, int> crate_counts;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int start = 0;
        int comma = line.find(',');
        while (comma != string::npos)
        {
            if (comma > start)
            {
                int crate_size = stoi(line.substr(start, comma - start));
                crate_counts[crate_size]++;
            }
            start = comma + 1;
            comma = line.find(',', start);
        }
        if (start < line.length())
        {
            int crate_size = stoi(line.substr(start));
            crate_counts[crate_size]++;
        }
    }
    int min_sets = 0;
    for (const pair<const int, int> &entry : crate_counts)
    {
        if (entry.second > min_sets)
            min_sets = entry.second;
    }
    output_file << min_sets << endl;
    return 0;
}