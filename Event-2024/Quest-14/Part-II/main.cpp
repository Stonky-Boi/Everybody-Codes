#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <tuple>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    set<tuple<long long, long long, long long>> tree_segments;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        long long current_x = 0;
        long long current_y = 0;
        long long current_z = 0;
        stringstream ss(line);
        string step;
        while (getline(ss, step, ','))
        {
            if (step.empty())
                continue;
            char direction = step[0];
            int distance = stoi(step.substr(1));
            for (int i = 0; i < distance; i++)
            {
                if (direction == 'U')
                    current_y++;
                else if (direction == 'D')
                    current_y--;
                else if (direction == 'R')
                    current_x++;
                else if (direction == 'L')
                    current_x--;
                else if (direction == 'F')
                    current_z++;
                else if (direction == 'B')
                    current_z--;
                tree_segments.insert({current_x, current_y, current_z});
            }
        }
    }
    output_file << tree_segments.size();
    return 0;
}