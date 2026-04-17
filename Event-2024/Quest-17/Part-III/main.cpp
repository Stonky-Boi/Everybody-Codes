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
public:
    vector<int> parent;
    vector<long long> component_size;
    vector<long long> component_mst_weight;

    DSU(int n)
    {
        parent.resize(n);
        component_size.resize(n, 1);
        component_mst_weight.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j, int weight)
    {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j)
        {
            parent[root_j] = root_i;
            component_size[root_i] += component_size[root_j];
            component_mst_weight[root_i] += component_mst_weight[root_j] + weight;
        }
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
            if (dist < 6)
                edges.push_back({i, j, dist});
        }
    }
    sort(edges.begin(), edges.end());
    DSU dsu(num_stars);
    for (const auto &e : edges)
        dsu.unite(e.u, e.v, e.weight);
    vector<long long> constellation_sizes;
    for (int i = 0; i < num_stars; i++)
    {
        if (dsu.parent[i] == i)
        {
            long long total_size = dsu.component_size[i] + dsu.component_mst_weight[i];
            constellation_sizes.push_back(total_size);
        }
    }
    sort(constellation_sizes.rbegin(), constellation_sizes.rend());
    long long product = constellation_sizes[0] * constellation_sizes[1] * constellation_sizes[2];
    output_file << product;
    return 0;
}