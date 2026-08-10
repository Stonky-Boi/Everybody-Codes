#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct interval
{
    int start;
    int end;

    bool operator<(const interval &other) const
    {
        return start < other.start;
    }
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    map<int, vector<interval>> openings;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        vector<int> values;
        int position = 0;
        while (position < line.length())
        {
            int comma = line.find(',', position);
            if (comma == string::npos)
                comma = line.length();
            string token = line.substr(position, comma - position);
            if (!token.empty())
                values.push_back(stoi(token));
            position = comma + 1;
        }
        if (values.size() >= 3)
        {
            int x = values[0];
            int y_start = values[1];
            int height = values[2];
            openings[x].push_back({y_start, y_start + height - 1});
        }
    }
    vector<interval> curr_intervals;
    curr_intervals.push_back({0, 0});
    int curr_x = 0;
    for (auto &[x, opening] : openings)
    {
        int dx = x - curr_x;
        vector<interval> expanded;
        for (const interval &i : curr_intervals)
            expanded.push_back({i.start - dx, i.end + dx});
        vector<interval> merged_expanded;
        if (!expanded.empty())
        {
            interval curr = expanded[0];
            for (int i = 1; i < expanded.size(); i++)
            {
                if (expanded[i].start <= curr.end)
                    curr.end = max(curr.end, expanded[i].end);
                else
                {
                    merged_expanded.push_back(curr);
                    curr = expanded[i];
                }
            }
            merged_expanded.push_back(curr);
        }
        sort(opening.begin(), opening.end());
        vector<interval> merged_openings;
        if (!opening.empty())
        {
            interval curr = opening[0];
            for (int i = 1; i < opening.size(); i++)
            {
                if (opening[i].start <= curr.end)
                    curr.end = max(curr.end, opening[i].end);
                else
                {
                    merged_openings.push_back(curr);
                    curr = opening[i];
                }
            }
            merged_openings.push_back(curr);
        }
        vector<interval> next_intervals;
        int i = 0;
        int j = 0;
        while (i < merged_expanded.size() && j < merged_openings.size())
        {
            int intersect_l = max(merged_expanded[i].start, merged_openings[j].start);
            int intersect_r = min(merged_expanded[i].end, merged_openings[j].end);
            if (intersect_l <= intersect_r)
            {
                int parity_l = intersect_l % 2;
                if (parity_l < 0)
                    parity_l += 2;
                int parity_x = x % 2;
                if (parity_x < 0)
                    parity_x += 2;
                if (parity_l != parity_x)
                    intersect_l++;
                int parity_r = intersect_r % 2;
                if (parity_r < 0)
                    parity_r += 2;
                if (parity_r != parity_x)
                    intersect_r--;
                if (intersect_l <= intersect_r)
                    next_intervals.push_back({intersect_l, intersect_r});
            }
            if (merged_expanded[i].end < merged_openings[j].end)
                i++;
            else
                j++;
        }
        curr_intervals = next_intervals;
        curr_x = x;
    }
    int minimum_flaps = (curr_x + curr_intervals[0].start) / 2;
    output_file << minimum_flaps << endl;
    return 0;
}