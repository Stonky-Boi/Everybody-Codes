#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<int> forward;
    vector<int> backward;
    string line;
    forward.push_back(1);
    int i = 0;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int dash = line.find('-');
        if (dash != string::npos)
        {
            int start = stoi(line.substr(0, dash));
            int end = stoi(line.substr(dash + 1));
            if (i % 2 == 0)
            {
                if (start <= end)
                {
                    for (int i = start; i <= end; i++)
                        forward.push_back(i);
                }
                else
                {
                    for (int i = start; i >= end; i--)
                        forward.push_back(i);
                }
            }
            else
            {
                if (start <= end)
                {
                    for (int i = start; i <= end; i++)
                        backward.push_back(i);
                }
                else
                {
                    for (int i = start; i >= end; i--)
                        backward.push_back(i);
                }
            }
            i++;
        }
    }
    vector<int> wheel = forward;
    for (auto it = backward.rbegin(); it != backward.rend(); it++)
        wheel.push_back(*it);
    int target = 20252025;
    int spots = wheel.size();
    int final_position = target % spots;
    output_file << wheel[final_position] << endl;
    return 0;
}