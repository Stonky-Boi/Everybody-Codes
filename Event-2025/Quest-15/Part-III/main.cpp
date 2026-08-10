#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct interval
{
    long long start;
    long long end;

    long long length() const
    {
        return end - start + 1;
    }
};

struct segment
{
    long long x1, y1, x2, y2;
};

long long distance(const interval &a, const interval &b)
{
    if (a.end < b.start)
        return b.start - a.end;
    if (a.start > b.end)
        return a.start - b.end;
    return 0;
}

void add(long long value, vector<long long> &values)
{
    values.push_back(value - 1);
    values.push_back(value);
    values.push_back(value + 1);
}

int get(long long value, vector<interval> &compressed)
{
    int l = 0, r = compressed.size() - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (compressed[m].start <= value && compressed[m].end >= value)
            return m;
        if (compressed[m].start > value)
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    vector<pair<char, long long>> instructions;
    int position = 0;
    while (position < line.length())
    {
        int comma = line.find(',', position);
        if (comma == string::npos)
            comma = line.length();
        string token = line.substr(position, comma - position);
        if (!token.empty())
        {
            char direction = token[0];
            long long length = stoll(token.substr(1));
            instructions.push_back({direction, length});
        }
        position = comma + 1;
    }
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    long long curr_x = 0;
    long long curr_y = 0;
    int curr_direction = 0;
    vector<segment> segments;
    vector<long long> x_values;
    vector<long long> y_values;
    add(0, x_values);
    add(0, y_values);
    for (int i = 0; i < instructions.size(); i++)
    {
        if (instructions[i].first == 'R')
            curr_direction = (curr_direction + 1) % 4;
        else if (instructions[i].first == 'L')
            curr_direction = (curr_direction + 3) % 4;
        long long next_x = curr_x + dx[curr_direction] * instructions[i].second;
        long long next_y = curr_y + dy[curr_direction] * instructions[i].second;
        long long start_x = curr_x + dx[curr_direction];
        long long start_y = curr_y + dy[curr_direction];
        segments.push_back({start_x, start_y, next_x, next_y});
        add(start_x, x_values);
        add(start_y, y_values);
        add(next_x, x_values);
        add(next_y, y_values);
        curr_x = next_x;
        curr_y = next_y;
    }
    long long target_x = curr_x;
    long long target_y = curr_y;
    sort(x_values.begin(), x_values.end());
    x_values.erase(unique(x_values.begin(), x_values.end()), x_values.end());
    sort(y_values.begin(), y_values.end());
    y_values.erase(unique(y_values.begin(), y_values.end()), y_values.end());
    vector<interval> compressed_x;
    for (int i = 0; i < x_values.size(); i++)
    {
        compressed_x.push_back({x_values[i], x_values[i]});
        if (i + 1 < x_values.size() && x_values[i] + 1 <= x_values[i + 1] - 1)
            compressed_x.push_back({x_values[i] + 1, x_values[i + 1] - 1});
    }
    vector<interval> compressed_y;
    for (int i = 0; i < y_values.size(); i++)
    {
        compressed_y.push_back({y_values[i], y_values[i]});
        if (i + 1 < y_values.size() && y_values[i] + 1 <= y_values[i + 1] - 1)
            compressed_y.push_back({y_values[i] + 1, y_values[i + 1] - 1});
    }
    int num_cx = compressed_x.size();
    int num_cy = compressed_y.size();
    vector<bool> wall((long long)num_cx * num_cy, false);
    for (int i = 0; i < segments.size(); i++)
    {
        int x_i1 = get(min(segments[i].x1, segments[i].x2), compressed_x);
        int x_i2 = get(max(segments[i].x1, segments[i].x2), compressed_x);
        int y_i1 = get(min(segments[i].y1, segments[i].y2), compressed_y);
        int y_i2 = get(max(segments[i].y1, segments[i].y2), compressed_y);
        for (int x = x_i1; x <= x_i2; x++)
        {
            for (int y = y_i1; y <= y_i2; y++)
                wall[(long long)y * num_cx + x] = true;
        }
    }
    int start_c_x = get(0, compressed_x);
    int start_c_y = get(0, compressed_y);
    int target_c_x = get(target_x, compressed_x);
    int target_c_y = get(target_y, compressed_y);
    wall[(long long)target_c_y * num_cx + target_c_x] = false;
    unordered_map<long long, long long> distances;
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
    long long start_node = (long long)start_c_y * num_cx + start_c_x;
    distances[start_node] = 0;
    pq.push({0LL, start_node});
    long long shortest_length = -1;
    while (!pq.empty())
    {
        auto [f_score, curr_node] = pq.top();
        pq.pop();
        int cy = curr_node / num_cx;
        int cx = curr_node % num_cx;
        long long curr_g = distances[curr_node];
        if (cx == target_c_x && cy == target_c_y)
        {
            shortest_length = curr_g / 2;
            break;
        }
        long long curr_h = distance(compressed_x[cx], compressed_x[target_c_x]) + distance(compressed_y[cy], compressed_y[target_c_y]);
        curr_h *= 2;
        if (curr_g + curr_h < f_score)
            continue;
        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx >= 0 && nx < num_cx && ny >= 0 && ny < num_cy)
            {
                long long next_node = (long long)ny * num_cx + nx;
                if (wall[next_node])
                    continue;
                long long step_cost = 0;
                if (dx[i] != 0)
                    step_cost = compressed_x[cx].length() + compressed_x[nx].length();
                else
                    step_cost = compressed_y[cy].length() + compressed_y[ny].length();
                long long next_g = curr_g + step_cost;
                unordered_map<long long, long long>::iterator it = distances.find(next_node);
                if (it == distances.end() || next_g < it->second)
                {
                    distances[next_node] = next_g;
                    long long h = distance(compressed_x[nx], compressed_x[target_c_x]) + distance(compressed_y[ny], compressed_y[target_c_y]);
                    h *= 2;
                    pq.push({next_g + h, next_node});
                }
            }
        }
    }
    output_file << shortest_length << endl;
    return 0;
}