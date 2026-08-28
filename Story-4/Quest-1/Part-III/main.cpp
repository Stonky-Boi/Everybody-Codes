#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct arc
{
    int u, v;
    int side;
};

bool crosses(const arc &a1, const arc &a2)
{
    if (a1.side != a2.side)
        return false;
    if (a1.u < a2.u && a2.u < a1.v && a1.v < a2.v)
        return true;
    if (a2.u < a1.u && a1.u < a2.v && a2.v < a1.v)
        return true;
    return false;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    int total_sum = 0;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        set<int> visited;
        vector<arc> arcs;
        int curr = 0;
        visited.insert(curr);
        int curr_side = 0;
        int position = 0;
        while (position < line.length())
        {
            int comma = line.find(',', position);
            if (comma == string::npos)
                comma = line.length();
            string token = line.substr(position, comma - position);
            if (token.empty())
            {
                position = comma + 1;
                continue;
            }
            int jump_length = stoll(token);
            bool jump_completed = false;
            int back_distance = curr - jump_length;
            if (back_distance > 0 && visited.find(back_distance) == visited.end())
            {
                arc curr_arc = {min(curr, back_distance), max(curr, back_distance), curr_side};
                bool valid = true;
                for (int i = 0; i < arcs.size(); ++i)
                {
                    if (crosses(curr_arc, arcs[i]))
                    {
                        valid = false;
                        break;
                    }
                }
                if (valid)
                {
                    curr = back_distance;
                    visited.insert(curr);
                    arcs.push_back(curr_arc);
                    curr_side ^= 1;
                    jump_completed = true;
                }
            }
            if (!jump_completed)
            {
                int forward_distance = curr + jump_length;
                int max_distance = -1;
                for (int i = 0; i < arcs.size(); ++i)
                {
                    if (arcs[i].side == curr_side && arcs[i].u < curr && curr < arcs[i].v)
                    {
                        if (max_distance == -1 || arcs[i].v < max_distance)
                            max_distance = arcs[i].v;
                    }
                }
                while (true)
                {
                    if (max_distance != -1 && forward_distance >= max_distance)
                        break;
                    if (visited.find(forward_distance) != visited.end())
                    {
                        forward_distance++;
                        continue;
                    }
                    arc curr_arc = {min(curr, forward_distance), max(curr, forward_distance), curr_side};
                    bool valid = true;
                    for (int i = 0; i < arcs.size(); ++i)
                    {
                        if (crosses(curr_arc, arcs[i]))
                        {
                            valid = false;
                            break;
                        }
                    }
                    if (valid)
                    {
                        curr = forward_distance;
                        visited.insert(curr);
                        arcs.push_back(curr_arc);
                        curr_side ^= 1;
                        jump_completed = true;
                        break;
                    }
                    else
                        forward_distance++;
                }
            }
            position = comma + 1;
        }
        total_sum += curr;
    }
    output_file << total_sum << endl;
    return 0;
}