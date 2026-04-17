#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;

struct star
{
    int id;
    int x, y;
};

struct edge
{
    int u, v;
    int weight;
    bool operator<(const edge &other) const
    {
        return weight < other.weight;
    }
};

class DSU
{
private:
    vector<int> parent;

public:
    DSU(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j)
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j)
            parent[root_i] = root_j;
    }
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    string line;
    while (getline(input_file, line))
    {
        if (!line.empty())
            grid.push_back(line);
    }
    int rows = grid.size();
    int columns = grid[0].size();
    vector<star> stars;
    int id_counter = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (grid[r][c] == '*')
            {
                int x = c;
                int y = rows - 1 - r;
                stars.push_back({id_counter++, x, y});
            }
        }
    }
    int num_stars = stars.size();
    vector<edge> edges;
    for (int i = 0; i < num_stars; i++)
    {
        for (int j = i + 1; j < num_stars; j++)
        {
            int dist = abs(stars[i].x - stars[j].x) + abs(stars[i].y - stars[j].y);
            edges.push_back({i, j, dist});
        }
    }
    sort(edges.begin(), edges.end());
    DSU dsu(num_stars);
    int mst_weight = 0;
    int edges_used = 0;
    for (const edge &e : edges)
    {
        if (dsu.find(e.u) != dsu.find(e.v))
        {
            dsu.unite(e.u, e.v);
            mst_weight += e.weight;
            edges_used++;
            if (edges_used == num_stars - 1)
                break;
        }
    }
    int constellation = mst_weight + num_stars;
    output_file << constellation;
    return 0;
}