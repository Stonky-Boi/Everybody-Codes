#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool valid_child(const string &potential, const string &parent_1, const string &parent_2)
{
    if (potential.length() != parent_1.length() || potential.length() != parent_2.length())
        return false;
    for (int i = 0; i < potential.length(); i++)
    {
        if (potential[i] != parent_1[i] && potential[i] != parent_2[i])
            return false;
    }
    return true;
}

int calculate_matches(const string &s1, const string &s2)
{
    int match_count = 0;
    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] == s2[i])
            match_count++;
    }
    return match_count;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<string> sequences;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int colon = line.find(':');
        if (colon != string::npos)
            sequences.push_back(line.substr(colon + 1));
    }
    int sum = 0;
    int num_ducks = sequences.size();
    for (int i = 0; i < num_ducks; ++i)
    {
        bool found_parents = false;
        for (int j = 0; j < num_ducks; ++j)
        {
            if (i == j)
                continue;
            for (int k = j + 1; k < num_ducks; ++k)
            {
                if (i == k)
                    continue;
                if (valid_child(sequences[i], sequences[j], sequences[k]))
                {
                    int matches_1 = calculate_matches(sequences[i], sequences[j]);
                    int matches_2 = calculate_matches(sequences[i], sequences[k]);
                    sum += (matches_1 * matches_2);
                    found_parents = true;
                    break;
                }
            }
            if (found_parents)
                break;
        }
    }
    output_file << sum << endl;
    return 0;
}