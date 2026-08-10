#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<string> lines;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        lines.push_back(line);
    }
    vector<long long> numerators;
    vector<long long> denominators;
    numerators.push_back(100);
    numerators.push_back(stoll(lines.front()));
    denominators.push_back(stoll(lines.back()));
    for (int i = 1; i < lines.size() - 1; i++)
    {
        int pipe = lines[i].find('|');
        if (pipe != string::npos)
        {
            long long left_gear = stoll(lines[i].substr(0, pipe));
            long long right_gear = stoll(lines[i].substr(pipe + 1));
            denominators.push_back(left_gear);
            numerators.push_back(right_gear);
        }
    }
    for (int i = 0; i < numerators.size(); i++)
    {
        for (int j = 0; j < denominators.size(); j++)
        {
            long long gcd_value = gcd(numerators[i], denominators[j]);
            if (gcd_value > 1)
            {
                numerators[i] /= gcd_value;
                denominators[j] /= gcd_value;
            }
        }
    }
    long long final_numerator = 1;
    for (int i = 0; i < numerators.size(); i++)
        final_numerator *= numerators[i];
    long long final_denominator = 1;
    for (int i = 0; i < denominators.size(); i++)
        final_denominator *= denominators[i];
    long long full_turns = final_numerator / final_denominator;
    output_file << full_turns << endl;
    return 0;
}