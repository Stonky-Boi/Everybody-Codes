#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<string> names;
    if (getline(input_file, line))
    {
        int start = 0;
        int comma = line.find(',');
        while (comma != string::npos)
        {
            names.push_back(line.substr(start, comma - start));
            start = comma + 1;
            comma = line.find(',', start);
        }
        if (start < line.length())
            names.push_back(line.substr(start));
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
    for (const string &name : names)
    {
        bool valid = true;
        for (int i = 0; i + 1 < name.length(); i++)
        {
            char curr_char = name[i];
            char next_char = name[i + 1];
            if (rules.find(curr_char) == rules.end() || rules.at(curr_char).find(next_char) == rules.at(curr_char).end())
            {
                valid = false;
                break;
            }
        }
        if (valid)
        {
            output_file << name << endl;
            break;
        }
    }
    return 0;
}