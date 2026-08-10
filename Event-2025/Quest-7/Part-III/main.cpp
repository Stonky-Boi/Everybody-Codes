#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

bool compare(const string &a, const string &b)
{
    if (a.length() != b.length())
        return a.length() < b.length();
    return a < b;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<string> prefixes;
    if (getline(input_file, line))
    {
        int start = 0;
        int comma = line.find(',');
        while (comma != string::npos)
        {
            prefixes.push_back(line.substr(start, comma - start));
            start = comma + 1;
            comma = line.find(',', start);
        }
        if (start < line.length())
            prefixes.push_back(line.substr(start));
    }
    map<char, set<char>> rules;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        char source = line[0];
        int arrow = line.find('>');
        if (arrow != string::npos)
        {
            for (int i = arrow + 1; i < line.length(); i++)
            {
                char target = line[i];
                if (target != ' ' && target != ',')
                    rules[source].insert(target);
            }
        }
    }
    vector<string> valid_prefixes;
    for (const string &p : prefixes)
    {
        bool valid = true;
        for (int i = 0; i + 1 < p.length(); i++)
        {
            if (rules.find(p[i]) == rules.end() || rules.at(p[i]).find(p[i + 1]) == rules.at(p[i]).end())
            {
                valid = false;
                break;
            }
        }
        if (valid)
            valid_prefixes.push_back(p);
    }
    sort(valid_prefixes.begin(), valid_prefixes.end(), compare);
    vector<string> minimal_prefixes;
    for (const string &p : valid_prefixes)
    {
        bool redundant = false;
        for (const string &m : minimal_prefixes)
        {
            if (p.length() >= m.length() && p.substr(0, m.length()) == m)
            {
                redundant = true;
                break;
            }
        }
        if (!redundant)
            minimal_prefixes.push_back(p);
    }
    int dp[12][256] = {0};
    for (int c = 0; c < 256; c++)
        dp[0][c] = 1;
    for (int i = 1; i <= 11; i++)
    {
        for (int c = 0; c < 256; c++)
        {
            dp[i][c] = 0;
            if (rules.find(c) != rules.end())
            {
                for (char next_c : rules.at(c))
                    dp[i][c] += dp[i - 1][next_c];
            }
        }
    }
    int total_names = 0;
    for (const string &p : minimal_prefixes)
    {
        int length = p.length();
        if (length > 11)
            continue;
        char last_char = p.back();
        int start_length = max(7, length);
        for (int target_length = start_length; target_length <= 11; target_length++)
        {
            int required_transitions = target_length - length;
            total_names += dp[required_transitions][last_char];
        }
    }
    output_file << total_names << endl;
    return 0;
}