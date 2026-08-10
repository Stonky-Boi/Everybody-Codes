#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

struct fast_edge
{
    int source_index;
    int weight;
};

struct fast_plant
{
    int thickness;
    int free_branch_index;
    int free_branch_weight;
    vector<fast_edge> edges;
};

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

int global_max_energy = 0;
vector<fast_plant> network;
vector<int> memo;
vector<int> useful_free_indices;
int target_index = -1;

void find_maximum_energy(int useful_index, int total_useful, vector<int> &curr_state)
{
    if (useful_index == total_useful)
    {
        for (int i = 0; i < network.size(); i++)
        {
            const fast_plant &plant = network[i];
            int incoming = 0;
            if (plant.free_branch_index != -1)
                incoming = curr_state[plant.free_branch_index] * plant.free_branch_weight;
            else
            {
                for (const fast_edge &e : plant.edges)
                    incoming += memo[e.source_index] * e.weight;
            }
            if (incoming >= plant.thickness)
                memo[i] = incoming;
            else
                memo[i] = 0;
        }
        int curr_energy = memo[target_index];
        if (curr_energy > global_max_energy)
            global_max_energy = curr_energy;
        return;
    }
    int free_index = useful_free_indices[useful_index];
    curr_state[free_index] = 0;
    find_maximum_energy(useful_index + 1, total_useful, curr_state);
    curr_state[free_index] = 1;
    find_maximum_energy(useful_index + 1, total_useful, curr_state);
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
            vector<int> curr_test;
            for (char c : line)
            {
                if (c == '0' || c == '1')
                    curr_test.push_back(c - '0');
            }
            testcases.push_back(curr_test);
            continue;
        }
        if (line.find("Plant ") == 0)
        {
            int with = line.find(" with thickness ");
            int colon = line.find(":");
            if (with != string::npos && colon != string::npos)
            {
                string id = line.substr(6, with - 6);
                string branch_thickness = line.substr(with + 16, colon - (with + 16));
                curr_plant = stoi(id);
                plant_thickness[curr_plant] = stoi(branch_thickness);
                if (indegree.find(curr_plant) == indegree.end())
                    indegree[curr_plant] = 0;
            }
        }
        else if (line.find("- free branch with thickness ") != string::npos)
        {
            int thick = line.find("thickness ") + 10;
            int branch_thickness = stoi(line.substr(thick));
            branches[curr_plant].push_back(make_pair(-1, branch_thickness));
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
                branches[curr_plant].push_back(make_pair(id, branch_thickness));
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
    map<int, int> original_to_compiled;
    network.resize(topo_order.size());
    memo.assign(topo_order.size(), 0);
    for (int i = 0; i < topo_order.size(); i++)
        original_to_compiled[topo_order[i]] = i;
    target_index = original_to_compiled[last_plant];
    for (int i = 0; i < topo_order.size(); i++)
    {
        int original_id = topo_order[i];
        network[i].thickness = plant_thickness[original_id];
        network[i].free_branch_index = -1;
        network[i].free_branch_weight = 0;
        for (int j = 0; j < branches[original_id].size(); j++)
        {
            int source = branches[original_id][j].first;
            int weight = branches[original_id][j].second;
            if (source == -1)
            {
                network[i].free_branch_index = free_index[original_id];
                network[i].free_branch_weight = weight;
            }
            else
            {
                fast_edge edge = {original_to_compiled[source], weight};
                network[i].edges.push_back(edge);
            }
        }
    }
    vector<int> max_out(network.size(), 0);
    for (int i = 0; i < network.size(); i++)
    {
        const fast_plant &p = network[i];
        int incoming = 0;
        if (p.free_branch_index != -1)
            incoming = p.free_branch_weight;
        else
        {
            for (const fast_edge &e : p.edges)
            {
                if (e.weight > 0)
                    incoming += max_out[e.source_index] * e.weight;
            }
        }
        if (incoming >= p.thickness)
            max_out[i] = incoming;
        else
            max_out[i] = 0;
    }
    for (int i = 0; i < network.size(); i++)
    {
        const fast_plant &p = network[i];
        if (p.free_branch_index != -1)
        {
            bool useful = false;
            for (int j = i + 1; j < network.size(); j++)
            {
                if (max_out[j] > 0)
                {
                    for (const fast_edge &e : network[j].edges)
                    {
                        if (e.source_index == i && e.weight > 0)
                        {
                            useful = true;
                            break;
                        }
                    }
                }
                if (useful)
                    break;
            }
            if (useful)
                useful_free_indices.push_back(p.free_branch_index);
        }
    }
    int free_branches = free_plants.size();
    vector<int> search_state(free_branches, 0);
    find_maximum_energy(0, useful_free_indices.size(), search_state);
    int total_deficit = 0;
    for (const vector<int> &t : testcases)
    {
        for (int i = 0; i < network.size(); i++)
        {
            const fast_plant &plant = network[i];
            int incoming = 0;
            if (plant.free_branch_index != -1)
            {
                if (plant.free_branch_index < t.size())
                    incoming = t[plant.free_branch_index] * plant.free_branch_weight;
            }
            else
            {
                for (const fast_edge &e : plant.edges)
                    incoming += memo[e.source_index] * e.weight;
            }
            if (incoming >= plant.thickness)
                memo[i] = incoming;
            else
                memo[i] = 0;
        }
        int duck_energy = memo[target_index];
        if (duck_energy > 0)
            total_deficit += (global_max_energy - duck_energy);
    }
    output_file << total_deficit << endl;
    return 0;
}