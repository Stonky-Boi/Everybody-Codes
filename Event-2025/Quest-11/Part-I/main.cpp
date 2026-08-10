#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<int> ducks;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        ducks.push_back(stoi(line));
    }
    int columns = ducks.size();
    int curr_round = 0;
    int target_rounds = 10;
    while (curr_round < target_rounds)
    {
        bool duck_moved = false;
        for (int i = 0; i < columns - 1; i++)
        {
            if (ducks[i] > ducks[i + 1])
            {
                ducks[i]--;
                ducks[i + 1]++;
                duck_moved = true;
            }
        }
        if (!duck_moved)
            break;
        curr_round++;
    }
    while (curr_round < target_rounds)
    {
        bool duck_moved = false;
        for (int i = 0; i < columns - 1; i++)
        {
            if (ducks[i] < ducks[i + 1])
            {
                ducks[i]++;
                ducks[i + 1]--;
                duck_moved = true;
            }
        }
        if (!duck_moved)
            break;
        curr_round++;
    }
    int flock_checksum = 0;
    for (int i = 0; i < columns; i++)
        flock_checksum += ducks[i] * (i + 1);
    output_file << flock_checksum << endl;
    return 0;
}