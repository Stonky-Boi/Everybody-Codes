#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> pattern;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        pattern.push_back(line);
    }
    long long p[8] = {0};
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (pattern[r][c] == '#')
                p[r] |= (1LL << c);
        }
    }
    map<vector<long long>, int> visited_states;
    vector<vector<long long>> state_history;
    vector<long long> active_counts;
    vector<bool> matches;
    long long s[36] = {0};
    long long mask = (1LL << 34) - 1;
    long long total_active = 0;
    int target_rounds = 1000000000;
    for (int t = 1; t <= target_rounds; t++)
    {
        long long ns[36] = {0};
        for (int r = 1; r <= 34; r++)
        {
            long long prev = s[r - 1];
            long long next = s[r + 1];
            long long parity = ((prev << 1) & mask) ^ (prev >> 1) ^ ((next << 1) & mask) ^ (next >> 1);
            ns[r] = s[r] ^ parity ^ mask;
        }
        vector<long long> curr_state(ns + 1, ns + 35);
        if (visited_states.find(curr_state) != visited_states.end())
        {
            int cycle_start = visited_states[curr_state];
            int cycle_length = t - cycle_start;
            int remaining_rounds = target_rounds - t + 1;
            long long active_sum = 0;
            for (int i = cycle_start; i < t; i++)
            {
                if (matches[i - 1])
                    active_sum += active_counts[i - 1];
            }
            total_active += (remaining_rounds / cycle_length) * active_sum;
            int remainder = remaining_rounds % cycle_length;
            for (int i = 0; i < remainder; i++)
            {
                if (matches[cycle_start - 1 + i])
                    total_active += active_counts[cycle_start - 1 + i];
            }
            break;
        }
        visited_states[curr_state] = t;
        state_history.push_back(curr_state);
        bool match = true;
        for (int i = 0; i < 8; i++)
        {
            if (((ns[14 + i] >> 13) & 0xFF) != p[i])
            {
                match = false;
                break;
            }
        }
        long long curr_active = 0;
        if (match)
        {
            for (int r = 1; r <= 34; r++)
                curr_active += __builtin_popcountll(ns[r]);
            total_active += curr_active;
        }
        active_counts.push_back(curr_active);
        matches.push_back(match);
        for (int i = 0; i < 36; i++)
            s[i] = ns[i];
    }
    output_file << total_active << endl;
    return 0;
}