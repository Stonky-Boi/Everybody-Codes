#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct plan
{
    char id;
    long long score;
};

bool compare(const plan &a, const plan &b)
{
    if (a.score == b.score)
        return a.id < b.id;
    return a.score > b.score;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<plan> plans;
    string line;
    while (input_file >> line)
    {
        if (line.empty())
            continue;
        char id = line[0];
        string actions = "";
        for (size_t i = 2; i < line.length(); i++)
        {
            if (line[i] != ',')
                actions += line[i];
        }
        long long power = 10;
        long long total_essence = 0;
        int length = actions.length();
        for (int i = 0; i < 10; i++)
        {
            char action = actions[i % length];
            if (action == '+')
                power++;
            else if (action == '-')
                power--;
            if (power < 0)
                power = 0;
            total_essence += power;
        }
        plans.push_back({id, total_essence});
    }
    sort(plans.begin(), plans.end(), compare);
    for (const plan &p : plans)
        output_file << p.id;
    return 0;
}