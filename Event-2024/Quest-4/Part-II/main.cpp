#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<int> nails;
    int length;
    while (input_file >> length)
        nails.push_back(length);
    int min_length = nails[0];
    for (int n : nails)
    {
        if (n < min_length)
            min_length = n;
    }
    long long strikes = 0;
    for (int n : nails)
        strikes += (n - min_length);
    output_file << strikes;
    return 0;
}