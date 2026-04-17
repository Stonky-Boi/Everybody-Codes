#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    map<string, vector<string>> rules;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        size_t colon_position = line.find(':');
        if (colon_position != string::npos)
        {
            string parent = line.substr(0, colon_position);
            string children_string = line.substr(colon_position + 1);
            vector<string> children;
            stringstream ss(children_string);
            string child;
            while (getline(ss, child, ','))
                children.push_back(child);
            rules[parent] = children;
        }
    }
    map<string, long long> population;
    population["A"] = 1;
    for (int day = 0; day < 4; day++)
    {
        map<string, long long> next_population;
        for (const auto &[type, count] : population)
        {
            if (rules.count(type))
            {
                for (const string &child : rules[type])
                    next_population[child] += count;
            }
        }
        population = next_population;
    }
    long long termites = 0;
    for (const auto &[_, count] : population)
        termites += count;
    output_file << termites;
    return 0;
}