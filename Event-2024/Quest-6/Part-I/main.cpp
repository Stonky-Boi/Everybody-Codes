#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

void dfs(const string &u, int depth, string path, const map<string, vector<string>> &adj, map<int, vector<string>> &length_paths)
{
    path += u;
    if (u == "@")
    {
        length_paths[depth].push_back(path);
        return;
    }
    if (adj.count(u))
    {
        for (const string &v : adj.at(u))
            dfs(v, depth + 1, path, adj, length_paths);
    }
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    map<string, vector<string>> adj;
    string line;
    while (input_file >> line)
    {
        size_t colon = line.find(':');
        string u = line.substr(0, colon);
        string child_string = line.substr(colon + 1);
        string v;
        for (char c : child_string)
        {
            if (c == ',')
            {
                adj[u].push_back(v);
                v = "";
            }
            else
                v += c;
        }
        if (!v.empty())
            adj[u].push_back(v);
    }
    map<int, vector<string>> length_paths;
    dfs("RR", 0, "", adj, length_paths);
    string path;
    for (const auto &[_, p] : length_paths)
    {
        if (p.size() == 1)
        {
            path = p[0];
            break;
        }
    }
    output_file << path;
    return 0;
}