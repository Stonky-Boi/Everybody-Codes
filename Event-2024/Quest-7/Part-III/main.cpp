#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

long long simulate(const string &plan, const string &track)
{
    long long power = 10;
    long long total_essence = 0;
    int action_index = 0;
    for (int loop = 0; loop < 11; loop++)
    {
        for (char t : track)
        {
            char action = plan[action_index % 11];
            action_index++;
            if (t == '+')
                power++;
            else if (t == '-')
                power--;
            else if (t == '=' || t == 'S')
            {
                if (action == '+')
                    power++;
                else if (action == '-')
                    power--;
            }
            if (power < 0)
                power = 0;

            total_essence += power;
        }
    }
    return total_essence;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string rival_plan = "";
    vector<string> grid;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (line.find(':') != string::npos)
        {
            size_t colon = line.find(':');
            for (size_t i = colon + 1; i < line.length(); i++)
            {
                if (line[i] != ',')
                    rival_plan += line[i];
            }
        }
        else
            grid.push_back(line);
    }
    int H = grid.size();
    int W = 0;
    for (const string &row : grid)
    {
        if (row.length() > W)
            W = row.length();
    }
    for (string &row : grid)
    {
        while (row.length() < W)
            row += ' ';
    }
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    int sr = -1, sc = -1;
    for (int r = 0; r < H; r++)
    {
        for (int c = 0; c < W; c++)
        {
            if (grid[r][c] == 'S')
            {
                sr = r;
                sc = c;
                break;
            }
        }
    }
    string track_sequence = "";
    int curr_row = sr, curr_column = sc;
    int prev_row = -1, prev_column = -1;
    if (sc + 1 < W && grid[sr][sc + 1] != ' ')
    {
        curr_row = sr;
        curr_column = sc + 1;
    }
    else
    {
        for (int d = 0; d < 4; d++)
        {
            int nr = sr + dr[d];
            int nc = sc + dc[d];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] != ' ')
            {
                curr_row = nr;
                curr_column = nc;
                break;
            }
        }
    }
    prev_row = sr;
    prev_column = sc;
    while (curr_row != sr || curr_column != sc)
    {
        track_sequence += grid[curr_row][curr_column];
        int next_row = -1, next_column = -1;
        for (int d = 0; d < 4; d++)
        {
            int nr = curr_row + dr[d];
            int nc = curr_column + dc[d];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W)
            {
                if (grid[nr][nc] != ' ' && (nr != prev_row || nc != prev_column))
                {
                    next_row = nr;
                    next_column = nc;
                    break;
                }
            }
        }
        prev_row = curr_row;
        prev_column = curr_column;
        curr_row = next_row;
        curr_column = next_column;
    }
    track_sequence += 'S';
    long long rival_score = simulate(rival_plan, track_sequence);
    string base_plan = "+++++---===";
    int winning_count = 0;
    do
    {
        long long score = simulate(base_plan, track_sequence);
        if (score > rival_score)
            winning_count++;
    } while (next_permutation(base_plan.begin(), base_plan.end()));
    output_file << winning_count;
    return 0;
}