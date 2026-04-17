#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<int> nails;
    int length;
    while (input_file >> length)
        nails.push_back(length);
    sort(nails.begin(), nails.end());
    int target_length = nails[nails.size() / 2];
    long long strikes = 0;
    for (int n : nails)
        strikes += abs(n - target_length);
    output_file << strikes;
    return 0;
}