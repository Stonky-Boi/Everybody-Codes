#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct spine_segment
{
    int value;
    bool left = false;
    bool right = false;

    spine_segment(int x) : value(x) {}
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    long long max_quality = -1;
    long long min_quality = -1;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int colon = line.find(':');
        string data = (colon != string::npos) ? line.substr(colon + 1) : line;
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
                        placed = true;
                        break;
                    }
                }
                else if (curr_number > spine[s].value)
                {
                    if (!spine[s].right)
                    {
                        spine[s].right = true;
                        placed = true;
                        break;
                    }
                }
            }
            if (!placed)
                spine.push_back(spine_segment(curr_number));
        }
        long long sword_quality = 0;
        for (const spine_segment &s : spine)
            sword_quality = sword_quality * 10 + s.value;
        if (max_quality == -1 || sword_quality > max_quality)
            max_quality = sword_quality;
        if (min_quality == -1 || sword_quality < min_quality)
            min_quality = sword_quality;
    }
    long long difference = max_quality - min_quality;
    output_file << difference << endl;
    return 0;
}