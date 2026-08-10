#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <utility>
using namespace std;

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
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
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
    queue<int> q;
    for (const auto &[node, count] : indegree)
    {
        if (count == 0)
            q.push(node);
    }
    map<int, int> plant_energy;
    int final_energy = 0;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        int incoming_energy = 0;
        for (const auto &[source, weight] : branches[curr])
        {
            if (source == -1)
                incoming_energy += weight;
            else
                incoming_energy += weight * plant_energy[source];
        }
        if (incoming_energy >= plant_thickness[curr])
            plant_energy[curr] = incoming_energy;
        else
            plant_energy[curr] = 0;
        if (adj[curr].empty())
            final_energy = plant_energy[curr];
        for (int next_plant : adj[curr])
        {
            indegree[next_plant]--;
            if (indegree[next_plant] == 0)
                q.push(next_plant);
        }
    }
    output_file << final_energy << endl;
    return 0;
}