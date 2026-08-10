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
    int similarity_degree = 0;
    for (int i = 0; i < sequences.size(); i++)
    {
        int parent_1 = (i + 1) % 3;
        int parent_2 = (i + 2) % 3;
        if (valid_child(sequences[i], sequences[parent_1], sequences[parent_2]))
        {
            int matches_1 = calculate_matches(sequences[i], sequences[parent_1]);
            int matches_2 = calculate_matches(sequences[i], sequences[parent_2]);
            similarity_degree = matches_1 * matches_2;
            break;
        }
    }
    output_file << similarity_degree << endl;
    return 0;
}