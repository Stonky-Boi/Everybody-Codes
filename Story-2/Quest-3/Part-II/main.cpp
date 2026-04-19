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
    string track;
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
            track = line;
    }
    vector<int> player_positions(dice.size(), 0);
    vector<bool> has_finished(dice.size(), false);
    vector<int> finishing_order;
    long long roll = 1;
    while (finishing_order.size() < dice.size())
    {
        for (size_t i = 0; i < dice.size(); i++)
        {
            if (has_finished[i])
            {
                roll_die(dice[i], roll);
                continue;
            }
            long long result = roll_die(dice[i], roll);
            int position = player_positions[i];
            long long target = track[position] - '0';
            if (result == target)
            {
                player_positions[i]++;
                if (player_positions[i] >= track.length())
                {
                    has_finished[i] = true;
                    finishing_order.push_back(dice[i].id);
                }
            }
        }
        roll++;
    }
    for (size_t i = 0; i < finishing_order.size(); i++)
    {
        output_file << finishing_order[i];
        if (i < finishing_order.size() - 1)
            output_file << ",";
    }
    return 0;
}