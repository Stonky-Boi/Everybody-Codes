#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

struct bit_set
{
    vector<long long> words;

    bit_set(int n = 0)
    {
        words.assign((n + 63) / 64, 0);
    }

    void set(int i)
    {
        words[i / 64] |= (1LL << (i % 64));
    }

    bool operator==(const bit_set &other) const
    {
        for (int i = 0; i < words.size(); i++)
        {
            if (words[i] != other.words[i])
                return false;
        }
        return true;
    }
};

int get_barrels(const bit_set &b, const vector<int> &component_size)
{
    int count = 0;
    for (int i = 0; i < b.words.size(); i++)
    {
        long long word = b.words[i];
        while (word)
        {
            int bit = __builtin_ctzll(word);
            count += component_size[i * 64 + bit];
            word &= word - 1;
        }
    }
    return count;
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<string> grid;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        grid.push_back(line);
    }
    int rows = grid.size();
    int columns = grid[0].size();
    vector<int> component_id(rows * columns, -1);
    vector<int> component_value;
    vector<int> component_size;
    int curr_component = 0;
    int row_moves[] = {-1, 1, 0, 0};
    int column_moves[] = {0, 0, -1, 1};
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            if (component_id[r * columns + c] == -1)
            {
                char value = grid[r][c];
                int size = 0;
                queue<pair<int, int>> q;
                q.push({r, c});
                component_id[r * columns + c] = curr_component;
                while (!q.empty())
                {
                    auto [curr_row, curr_column] = q.front();
                    q.pop();
                    size++;
                    for (int i = 0; i < 4; i++)
                    {
                        int next_row = curr_row + row_moves[i];
                        int next_column = curr_column + column_moves[i];
                        if (next_row >= 0 && next_row < rows && next_column >= 0 && next_column < columns)
                        {
                            if (component_id[next_row * columns + next_column] == -1 && grid[next_row][next_column] == value)
                            {
                                component_id[next_row * columns + next_column] = curr_component;
                                q.push({next_row, next_column});
                            }
                        }
                    }
                }
                component_value.push_back(value - '0');
                component_size.push_back(size);
                curr_component++;
            }
        }
    }
    int components = curr_component;
    vector<vector<int>> adj(components);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            int u = component_id[r * columns + c];
            for (int i = 0; i < 4; i++)
            {
                int next_row = r + row_moves[i];
                int next_column = c + column_moves[i];
                if (next_row >= 0 && next_row < rows && next_column >= 0 && next_column < columns)
                {
                    int v = component_id[next_row * columns + next_column];
                    if (component_value[u] > component_value[v])
                        adj[u].push_back(v);
                }
            }
        }
    }
    for (int i = 0; i < components; i++)
    {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }
    vector<bit_set> reach(components, bit_set(components));
    for (int value = 0; value <= 9; value++)
    {
        for (int i = 0; i < components; i++)
        {
            if (component_value[i] == value)
            {
                reach[i].set(i);
                for (int v : adj[i])
                {
                    for (int w = 0; w < reach[i].words.size(); w++)
                        reach[i].words[w] |= reach[v].words[w];
                }
            }
        }
    }
    vector<int> sorted_components(components);
    for (int i = 0; i < components; i++)
        sorted_components[i] = i;
    vector<int> component_reach_count(components);
    for (int i = 0; i < components; i++)
        component_reach_count[i] = get_barrels(reach[i], component_size);
    sort(sorted_components.begin(), sorted_components.end(), [&](int a, int b)
         { return component_reach_count[a] > component_reach_count[b]; });
    int max1 = 0;
    vector<int> c1_options;
    for (int i = 0; i < components; i++)
    {
        int c = component_reach_count[i];
        if (c > max1)
        {
            max1 = c;
            c1_options = {i};
        }
        else if (c == max1)
            c1_options.push_back(i);
    }
    int max2 = 0;
    vector<bit_set> c2_reach;
    for (int u : c1_options)
    {
        for (int v : sorted_components)
        {
            if (max1 + component_reach_count[v] < max2)
                break;
            bit_set combined = reach[u];
            for (int w = 0; w < combined.words.size(); w++)
                combined.words[w] |= reach[v].words[w];
            int c = get_barrels(combined, component_size);
            if (c > max2)
            {
                max2 = c;
                c2_reach = {combined};
            }
            else if (c == max2)
            {
                bool duplicate = false;
                for (const bit_set &existing : c2_reach)
                {
                    if (existing == combined)
                    {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate)
                    c2_reach.push_back(combined);
            }
        }
    }
    int max3 = 0;
    for (const bit_set &uv : c2_reach)
    {
        for (int w : sorted_components)
        {
            if (max2 + component_reach_count[w] <= max3)
                break;
            bit_set combined = uv;
            for (int k = 0; k < combined.words.size(); k++)
                combined.words[k] |= reach[w].words[k];
            int c = get_barrels(combined, component_size);
            if (c > max3)
                max3 = c;
        }
    }
    output_file << max3 << endl;
    return 0;
}