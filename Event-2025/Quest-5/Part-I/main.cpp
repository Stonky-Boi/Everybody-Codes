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
    getline(input_file, line);
    int colon = line.find(':');
    if (colon != string::npos)
        line = line.substr(colon + 1);
    vector<int> numbers;
    int start = 0;
    int comma = line.find(',');
    while (comma != string::npos)
    {
        numbers.push_back(stoi(line.substr(start, comma - start)));
        start = comma + 1;
        comma = line.find(',', start);
    }
    if (start < line.length())
        numbers.push_back(stoi(line.substr(start)));
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
    output_file << sword_quality << endl;
    return 0;
}