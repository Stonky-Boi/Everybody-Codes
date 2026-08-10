#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct spine_segment
{
    int value;
    bool left = false;
    int left_value = 0;
    bool right = false;
    int right_value = 0;

    spine_segment(int x) : value(x) {}
};

struct sword
{
    int id;
    long long quality;
    vector<int> levels;
};

bool compare(const sword &a, const sword &b)
{
    if (a.quality != b.quality)
        return a.quality > b.quality;
    int min_levels = min(a.levels.size(), b.levels.size());
    for (int i = 0; i < min_levels; i++)
    {
        if (a.levels[i] != b.levels[i])
            return a.levels[i] > b.levels[i];
    }
    if (a.levels.size() != b.levels.size())
        return a.levels.size() > b.levels.size();
    return a.id > b.id;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<sword> swords;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int colon = line.find(':');
        int id = stoi(line.substr(0, colon));
        string data = line.substr(colon + 1);
        vector<int> numbers;
        int start = 0;
        int comma = data.find(',');
        while (comma != string::npos)
        {
            numbers.push_back(stoi(data.substr(start, comma - start)));
            start = comma + 1;
            comma = data.find(',', start);
        }
        if (start < data.length())
            numbers.push_back(stoi(data.substr(start)));
        vector<spine_segment> spine;
        spine.push_back(spine_segment(numbers[0]));
        for (int i = 1; i < numbers.size(); i++)
        {
            int curr_number = numbers[i];
            bool placed = false;
            for (int s = 0; s < spine.size(); s++)
            {
                if (curr_number < spine[s].value)
                {
                    if (!spine[s].left)
                    {
                        spine[s].left = true;
                        spine[s].left_value = curr_number;
                        placed = true;
                        break;
                    }
                }
                else if (curr_number > spine[s].value)
                {
                    if (!spine[s].right)
                    {
                        spine[s].right = true;
                        spine[s].right_value = curr_number;
                        placed = true;
                        break;
                    }
                }
            }
            if (!placed)
                spine.push_back(spine_segment(curr_number));
        }
        sword curr_sword;
        curr_sword.id = id;
        long long quality = 0;
        for (const spine_segment &s : spine)
        {
            quality = quality * 10 + s.value;
            int level = s.value;
            if (s.left)
                level = s.left_value * 10 + level;
            if (s.right)
                level = level * 10 + s.right_value;
            curr_sword.levels.push_back(level);
        }
        curr_sword.quality = quality;
        swords.push_back(curr_sword);
    }
    sort(swords.begin(), swords.end(), compare);
    long long checksum = 0;
    for (int i = 0; i < swords.size(); i++)
        checksum += swords[i].id * (i + 1);
    output_file << checksum << endl;
    return 0;
}