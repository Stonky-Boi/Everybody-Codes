#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    vector<pair<char, int>> instructions;
    int position = 0;
    while (position < line.length())
    {
        int comma = line.find(',', position);
        if (comma == string::npos)
            comma = line.length();
        string token = line.substr(position, comma - position);
        if (!token.empty())
        {
            char direction = token[0];
            int length = stoi(token.substr(1));
            instructions.push_back({direction, length});
        }
        position = comma + 1;
    }
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    int curr_x = 0;
    int curr_y = 0;
    int curr_direction = 0;
    int min_x = 0, max_x = 0;
    int min_y = 0, max_y = 0;
    for (int i = 0; i < instructions.size(); i++)
    {
        if (instructions[i].first == 'R')
            curr_direction = (curr_direction + 1) % 4;
        else if (instructions[i].first == 'L')
            curr_direction = (curr_direction + 3) % 4;
        for (int step = 0; step < instructions[i].second; step++)
        {
            curr_x += dx[curr_direction];
            curr_y += dy[curr_direction];
            if (curr_x < min_x)
                min_x = curr_x;
            if (curr_x > max_x)
                max_x = curr_x;
            if (curr_y < min_y)
                min_y = curr_y;
            if (curr_y > max_y)
                max_y = curr_y;
        }
    }
    min_x -= 3;
    max_x += 3;
    min_y -= 3;
    max_y += 3;
    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;
    vector<char> grid(width * height, 0);
    curr_x = -min_x;
    curr_y = -min_y;
    curr_direction = 0;
    for (int i = 0; i < instructions.size(); i++)
    {
        if (instructions[i].first == 'R')
            curr_direction = (curr_direction + 1) % 4;
        else if (instructions[i].first == 'L')
            curr_direction = (curr_direction + 3) % 4;
        for (int step = 0; step < instructions[i].second; step++)
        {
            curr_x += dx[curr_direction];
            curr_y += dy[curr_direction];
            grid[curr_y * width + curr_x] = 1;
        }
    }
    grid[curr_y * width + curr_x] = 2;
    int start_x = -min_x;
    int start_y = -min_y;
    queue<pair<int, int>> q;
    vector<int> distance(width * height, -1);
    q.push({start_x, start_y});
    distance[start_y * width + start_x] = 0;
    int shortest_length = -1;
    while (!q.empty())
    {
        auto [cx, cy] = q.front();
        q.pop();
        if (grid[cy * width + cx] == 2)
        {
            shortest_length = distance[cy * width + cx];
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
            {
                if (grid[ny * width + nx] != 1 && distance[ny * width + nx] == -1)
                {
                    distance[ny * width + nx] = distance[cy * width + cx] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    output_file << shortest_length << endl;
    return 0;
}