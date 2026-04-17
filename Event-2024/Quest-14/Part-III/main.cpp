#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
using namespace std;

struct point
{
    long long x;
    long long y;
    long long z;

    bool operator<(const point &other) const
    {
        if (x != other.x)
            return x < other.x;
        if (y != other.y)
            return y < other.y;
        return z < other.z;
    }

    bool operator==(const point &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

int get_id(const vector<point> &points, const point &p)
{
    vector<point>::const_iterator it = lower_bound(points.begin(), points.end(), p);
    if (it != points.end() && *it == p)
        return distance(points.begin(), it);
    return -1;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<point> points, leaves;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        point curr_point = {0, 0, 0};
        points.push_back(curr_point);
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
                    curr_point.y++;
                else if (direction == 'D')
                    curr_point.y--;
                else if (direction == 'R')
                    curr_point.x++;
                else if (direction == 'L')
                    curr_point.x--;
                else if (direction == 'F')
                    curr_point.z++;
                else if (direction == 'B')
                    curr_point.z--;
                points.push_back(curr_point);
            }
        }
        leaves.push_back(curr_point);
    }
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    int unique_points = points.size();
    vector<vector<int>> adjacency_list(unique_points);
    point directions[6] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
    for (int i = 0; i < unique_points; i++)
    {
        for (int d = 0; d < 6; d++)
        {
            point neighbor = {
                points[i].x + directions[d].x,
                points[i].y + directions[d].y,
                points[i].z + directions[d].z};
            int neighbor_id = get_id(points, neighbor);
            if (neighbor_id != -1)
                adjacency_list[i].push_back(neighbor_id);
        }
    }
    vector<int> trunk_ids;
    for (int i = 0; i < unique_points; i++)
    {
        if (points[i].x == 0 && points[i].z == 0 && points[i].y >= 0)
            trunk_ids.push_back(i);
    }
    vector<int> leaf_ids;
    for (const point &leaf : leaves)
        leaf_ids.push_back(get_id(points, leaf));
    vector<long long> total_murkiness(unique_points, 0);
    vector<bool> reachable(unique_points, true);
    for (int leaf_id : leaf_ids)
    {
        vector<int> distances(unique_points, -1);
        queue<int> q;
        q.push(leaf_id);
        distances[leaf_id] = 0;
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            for (int neighbor : adjacency_list[curr])
            {
                if (distances[neighbor] == -1)
                {
                    distances[neighbor] = distances[curr] + 1;
                    q.push(neighbor);
                }
            }
        }
        for (int id : trunk_ids)
        {
            if (distances[id] == -1)
                reachable[id] = false;
            else
                total_murkiness[id] += distances[id];
        }
    }
    long long min_murkiness = -1;
    for (int id : trunk_ids)
    {
        if (reachable[id])
        {
            if (min_murkiness == -1 || total_murkiness[id] < min_murkiness)
                min_murkiness = total_murkiness[id];
        }
    }
    output_file << min_murkiness;
    return 0;
}