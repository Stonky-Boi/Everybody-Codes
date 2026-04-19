#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct die
{
    int id;
    vector<long long> faces;
    long long seed;
    long long pulse;
    int curr_face_id;
};

long long roll_die(die &d, long long roll)
{
    long long spin = roll * d.pulse;
    int num_faces = d.faces.size();
    d.curr_face_id = (d.curr_face_id + spin) % num_faces;
    long long result = d.faces[d.curr_face_id];
    d.pulse = d.pulse + spin;
    d.pulse = d.pulse % d.seed;
    d.pulse = d.pulse + 1 + roll + d.seed;
    return result;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<die> dice;
    vector<string> grid;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (line.find("faces=") != string::npos)
        {
            die curr_die;
            curr_die.curr_face_id = 0;
            size_t colon = line.find(':');
            curr_die.id = stoi(line.substr(0, colon));
            size_t bracket_open = line.find('[');
            size_t bracket_close = line.find(']');
            string faces_string = line.substr(bracket_open + 1, bracket_close - bracket_open - 1);
            size_t start = 0;
            size_t comma = faces_string.find(',');
            while (comma != string::npos)
            {
                curr_die.faces.push_back(stoll(faces_string.substr(start, comma - start)));
                start = comma + 1;
                comma = faces_string.find(',', start);
            }
            curr_die.faces.push_back(stoll(faces_string.substr(start)));
            size_t seed_position = line.find("seed=");
            curr_die.seed = stoll(line.substr(seed_position + 5));
            curr_die.pulse = curr_die.seed;
            dice.push_back(curr_die);
        }
        else
        {
            grid.push_back(line);
        }
    }
    int num_rows = grid.size();
    int num_columns = grid[0].size();
    vector<vector<bool>> visited(num_rows, vector<bool>(num_columns, false));
    int direction_row[] = {0, -1, 1, 0, 0};
    int direction_column[] = {0, 0, 0, -1, 1};
    for (size_t i = 0; i < dice.size(); i++)
    {
        long long roll = 1;
        long long first = roll_die(dice[i], roll++);
        vector<pair<int, int>> active_list;
        for (int r = 0; r < num_rows; r++)
        {
            for (int c = 0; c < num_columns; c++)
            {
                if (grid[r][c] - '0' == first)
                {
                    active_list.push_back({r, c});
                    visited[r][c] = true;
                }
            }
        }
        while (!active_list.empty())
        {
            long long next = roll_die(dice[i], roll++);
            vector<vector<bool>> next_active_grid(num_rows, vector<bool>(num_columns, false));
            vector<pair<int, int>> next_active_list;
            for (const auto &[curr_row, curr_column] : active_list)
            {
                for (int d = 0; d < 5; d++)
                {
                    int next_row = curr_row + direction_row[d];
                    int next_column = curr_column + direction_column[d];
                    if (next_row >= 0 && next_row < num_rows && next_column >= 0 && next_column < num_columns)
                    {
                        if (!next_active_grid[next_row][next_column])
                        {
                            if (grid[next_row][next_column] - '0' == next)
                            {
                                next_active_grid[next_row][next_column] = true;
                                next_active_list.push_back({next_row, next_column});
                                visited[next_row][next_column] = true;
                            }
                        }
                    }
                }
            }
            active_list = next_active_list;
        }
    }
    long long max_prize_pool = 0;
    for (int r = 0; r < num_rows; r++)
    {
        for (int c = 0; c < num_columns; c++)
        {
            if (visited[r][c])
                max_prize_pool++;
        }
    }
    output_file << max_prize_pool;
    return 0;
}