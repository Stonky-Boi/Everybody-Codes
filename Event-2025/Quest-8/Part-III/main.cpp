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
    int nails = 256;
    vector<vector<int>> diff(nails + 2, vector<int>(nails + 2, 0));
    vector<vector<int>> exact(nails + 2, vector<int>(nails + 2, 0));
    for (int i = 1; i < sequence.size(); i++)
    {
        int u = min(sequence[i - 1], sequence[i]);
        int v = max(sequence[i - 1], sequence[i]);
        if (u == v)
            continue;
        exact[u][v]++;
        if (u - 1 >= 1 && v - 1 >= u + 1)
        {
            int r1 = 1, r2 = u - 1;
            int c1 = u + 1, c2 = v - 1;
            diff[r1][c1]++;
            diff[r1][c2 + 1]--;
            diff[r2 + 1][c1]--;
            diff[r2 + 1][c2 + 1]++;
        }
        if (v - 1 >= u + 1 && nails >= v + 1)
        {
            int r1 = u + 1, r2 = v - 1;
            int c1 = v + 1, c2 = nails;
            diff[r1][c1]++;
            diff[r1][c2 + 1]--;
            diff[r2 + 1][c1]--;
            diff[r2 + 1][c2 + 1]++;
        }
    }
    int max_cuts = 0;
    for (int a = 1; a <= nails; a++)
    {
        for (int b = 1; b <= nails; b++)
        {
            diff[a][b] += diff[a - 1][b] + diff[a][b - 1] - diff[a - 1][b - 1];
            if (a < b)
                max_cuts = max(max_cuts, diff[a][b] + exact[a][b]);
        }
    }
    output_file << max_cuts << endl;
    return 0;
}