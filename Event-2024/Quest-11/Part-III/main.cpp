#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <limits>
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
    long long max_population = 0;
    long long min_population = numeric_limits<long long>::max();
    for (const auto &[start_type, _] : rules)
    {
        map<string, long long> population;
        population[start_type] = 1;
        for (int day = 0; day < 20; day++)
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
        long long curr_population = 0;
        for (const auto &[_, count] : population)
            curr_population += count;
        if (curr_population > max_population)
            max_population = curr_population;
        if (curr_population < min_population)
            min_population = curr_population;
    }
    long long difference = max_population - min_population;
    output_file << difference;
    return 0;
}