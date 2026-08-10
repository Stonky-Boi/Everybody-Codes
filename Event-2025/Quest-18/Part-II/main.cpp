#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

bool testcase(const string &line)
{
    if (line.empty())
        return false;
    bool has_digit = false;
    for (char c : line)
    {
        if (c == '0' || c == '1')
            has_digit = true;
        else if (c != ' ')
            return false;
    }
    return has_digit;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    int curr_plant = -1;
    map<int, int> plant_thickness;
    map<int, vector<pair<int, int>>> branches;
    map<int, int> indegree;
    map<int, vector<int>> adj;
    vector<vector<int>> testcases;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (testcase(line))
        {
            vector<int> current_test;
            for (char c : line)
            {
                if (c == '0' || c == '1')
                    current_test.push_back(c - '0');
            }
            testcases.push_back(current_test);
            continue;
        }
        if (line.find("Plant ") == 0)
        {
            int with = line.find(" with thickness ");
            int colon = line.find(":");
            if (with != string::npos && colon != string::npos)
            {
                string id = line.substr(6, with - 6);
                string branch_thick = line.substr(with + 16, colon - (with + 16));
                curr_plant = stoi(id);
                plant_thickness[curr_plant] = stoi(branch_thick);
                if (indegree.find(curr_plant) == indegree.end())
                    indegree[curr_plant] = 0;
            }
        }
        else if (line.find("- free branch with thickness ") != string::npos)
        {
            int thick = line.find("thickness ") + 10;
            int branch_thickness = stoi(line.substr(thick));
            branches[curr_plant].push_back({-1, branch_thickness});
        }
        else if (line.find("- branch to Plant ") != string::npos)
        {
            int plant = line.find("Plant ") + 6;
            int with = line.find(" with thickness ");
            if (with != string::npos)
            {
                string source = line.substr(plant, with - plant);
                int thick = with + 16;
                string branch_thick = line.substr(thick);
                int id = stoi(source);
                int branch_thickness = stoi(branch_thick);
                branches[curr_plant].push_back({id, branch_thickness});
                indegree[curr_plant]++;
                adj[id].push_back(curr_plant);
                if (indegree.find(id) == indegree.end())
                    indegree[id] = 0;
            }
        }
    }
    vector<int> free_plants;
    for (const auto &[plant, branch] : branches)
    {
        for (const auto &[id, _] : branch)
        {
            if (id == -1)
            {
                free_plants.push_back(plant);
                break;
            }
        }
    }
    sort(free_plants.begin(), free_plants.end());
    map<int, int> free_index;
    for (int i = 0; i < free_plants.size(); i++)
        free_index[free_plants[i]] = i;
    queue<int> q;
    for (const auto &[node, count] : indegree)
    {
        if (count == 0)
            q.push(node);
    }
    vector<int> topo_order;
    int last_plant = -1;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        topo_order.push_back(curr);
        if (adj[curr].empty())
            last_plant = curr;
        for (int next_plant : adj[curr])
        {
            indegree[next_plant]--;
            if (indegree[next_plant] == 0)
                q.push(next_plant);
        }
    }
    long long total_energy_sum = 0;
    for (const vector<int> &t : testcases)
    {
        map<int, long long> plant_energy;
        for (int curr : topo_order)
        {
            long long incoming_energy = 0;
            for (const auto &[source, weight] : branches[curr])
            {
                if (source == -1)
                {
                    int i = free_index[curr];
                    if (i >= 0 && i < t.size())
                        incoming_energy += t[i] * weight;
                }
                else
                    incoming_energy += weight * plant_energy[source];
            }
            if (incoming_energy >= plant_thickness[curr])
                plant_energy[curr] = incoming_energy;
            else
                plant_energy[curr] = 0;
        }
        if (last_plant != -1)
            total_energy_sum += plant_energy[last_plant];
    }
    output_file << total_energy_sum << endl;
    return 0;
}