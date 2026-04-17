#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

const long long INF = 1e18;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    vector<int> advances;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ','))
        advances.push_back(stoi(token));
    int num_wheels = advances.size();
    vector<vector<string>> wheels(num_wheels);
    vector<int> lengths(num_wheels, 0);
    getline(input_file, line); // skip empty line
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        for (int i = 0; i < num_wheels; ++i)
        {
            if (i * 4 < line.length())
            {
                int length = min(3, (int)line.length() - i * 4);
                string symbol = line.substr(i * 4, length);
                if (symbol.length() >= 3 && symbol != "   ")
                {
                    string eyes = "";
                    eyes += symbol[0];
                    eyes += symbol[2];
                    wheels[i].push_back(eyes);
                }
            }
        }
    }
    for (int i = 0; i < num_wheels; ++i)
        lengths[i] = wheels[i].size();
    const int OFFSET = 300; // to keep array indices positive due to range from -256 to 256
    vector<long long> dp_max(600, -1);
    vector<long long> dp_min(600, INF);
    dp_max[OFFSET] = 0;
    dp_min[OFFSET] = 0;
    for (int k = 1; k <= 256; ++k)
    {
        vector<long long> next_dp_max(600, -1);
        vector<long long> next_dp_min(600, INF);
        int min_l_prev = OFFSET - (k - 1);
        int max_l_prev = OFFSET + (k - 1);
        for (int l_prev_off = min_l_prev; l_prev_off <= max_l_prev; ++l_prev_off)
        {
            if (dp_max[l_prev_off] == -1)
                continue;
            for (int dl : {-1, 0, 1})
            {
                int l_off = l_prev_off + dl;
                int L = l_off - OFFSET;
                long long score = 0;
                int counts[256] = {0};
                vector<char> seen;
                for (int i = 0; i < num_wheels; ++i)
                {
                    int idx = (L + k * advances[i]) % lengths[i];
                    if (idx < 0)
                        idx += lengths[i];
                    char left_eye = wheels[i][idx][0];
                    char right_eye = wheels[i][idx][1];
                    if (counts[left_eye] == 0)
                        seen.push_back(left_eye);
                    counts[left_eye]++;
                    if (counts[right_eye] == 0)
                        seen.push_back(right_eye);
                    counts[right_eye]++;
                }
                for (char c : seen)
                {
                    if (counts[c] >= 3)
                        score += (counts[c] - 2);
                }
                next_dp_max[l_off] = max(next_dp_max[l_off], dp_max[l_prev_off] + score);
                next_dp_min[l_off] = min(next_dp_min[l_off], dp_min[l_prev_off] + score);
            }
        }
        dp_max = next_dp_max;
        dp_min = next_dp_min;
    }
    long long global_max = -1, global_min = INF;
    for (int i = 0; i < 600; ++i)
    {
        if (dp_max[i] != -1)
        {
            global_max = max(global_max, dp_max[i]);
            global_min = min(global_min, dp_min[i]);
        }
    }
    output_file << global_max << " " << global_min;
    return 0;
}