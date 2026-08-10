#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

struct dragonduck
{
    int id;
    string dna;
};

bool valid_child(const string &potential, const string &parent_1, const string &parent_2)
{
    if (potential.length() != parent_1.length() || potential.length() != parent_2.length())
        return false;
    for (int i = 0; i < potential.length(); i++)
    {
        if (potential[i] != parent_1[i] && potential[i] != parent_2[i])
            return false;
    }
    return true;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<dragonduck> ducks;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int colon = line.find(':');
        if (colon != string::npos)
        {
            dragonduck curr_duck;
            curr_duck.id = stoi(line.substr(0, colon));
            curr_duck.dna = line.substr(colon + 1);
            ducks.push_back(curr_duck);
        }
    }
    int num_ducks = ducks.size();
    map<int, vector<int>> adj;
    for (const dragonduck &duck : ducks)
        adj[duck.id] = vector<int>();
    for (int i = 0; i < num_ducks; i++)
    {
        bool found_parents = false;
        for (int j = 0; j < num_ducks; j++)
        {
            if (i == j)
                continue;
            for (int k = j + 1; k < num_ducks; k++)
            {
                if (i == k)
                    continue;
                if (valid_child(ducks[i].dna, ducks[j].dna, ducks[k].dna))
                {
                    adj[ducks[i].id].push_back(ducks[j].id);
                    adj[ducks[j].id].push_back(ducks[i].id);
                    adj[ducks[i].id].push_back(ducks[k].id);
                    adj[ducks[k].id].push_back(ducks[i].id);
                    found_parents = true;
                    break;
                }
            }
            if (found_parents)
                break;
        }
    }
    set<int> visited;
    int max_size = 0;
    int max_sum = 0;
    for (const dragonduck &duck : ducks)
    {
        int start = duck.id;
        if (visited.find(start) == visited.end())
        {
            stack<int> st;
            st.push(start);
            visited.insert(start);
            int curr_size = 0;
            int curr_sum = 0;
            while (!st.empty())
            {
                int curr_node = st.top();
                st.pop();
                curr_size++;
                curr_sum += curr_node;
                for (int neighbor : adj[curr_node])
                {
                    if (visited.find(neighbor) == visited.end())
                    {
                        visited.insert(neighbor);
                        st.push(neighbor);
                    }
                }
            }
            if (curr_size > max_size)
            {
                max_size = curr_size;
                max_sum = curr_sum;
            }
        }
    }
    output_file << max_sum << endl;
    return 0;
}