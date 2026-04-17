#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct plan
{
    char id;
    string actions;
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
    vector<string> grid;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (line.find(':') != string::npos)
        {
            char id = line[0];
            string actions = "";
            for (size_t i = 2; i < line.length(); i++)
            {
                if (line[i] != ',')
                    actions += line[i];
            }
            plans.push_back({id, actions, 0});
        }
        else
            grid.push_back(line);
    }
    if (grid.empty())
        return 0;
    int H = grid.size();
    int W = grid[0].length();
    string track_sequence = "";
    for (int c = 1; c < W; c++)
        track_sequence += grid[0][c];
    for (int r = 1; r < H; r++)
        track_sequence += grid[r][W - 1];
    for (int c = W - 2; c >= 0; c--)
        track_sequence += grid[H - 1][c];
    for (int r = H - 2; r >= 0; r--)
        track_sequence += grid[r][0];
    for (plan &p : plans)
    {
        long long power = 10;
        long long total_essence = 0;
        int action_index = 0;
        int length = p.actions.length();
        for (int loop = 0; loop < 10; loop++)
        {
            for (char t : track_sequence)
            {
                char action = p.actions[action_index % length];
                action_index++;
                if (t == '+')
                    power++;
                else if (t == '-')
                    power--;
                else if (t == '=' || t == 'S')
                {
                    if (action == '+')
                        power++;
                    else if (action == '-')
                        power--;
                }
                if (power < 0)
                    power = 0;
                total_essence += power;
            }
        }
        p.score = total_essence;
    }
    sort(plans.begin(), plans.end(), compare);
    for (const plan &p : plans)
        output_file << p.id;
    return 0;
}