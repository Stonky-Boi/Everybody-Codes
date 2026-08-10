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
    int total_rounds = 0;
    while (true)
    {
        bool duck_moved = false;
        for (int i = 0; i < columns - 1; ++i)
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
        total_rounds++;
    }
    while (true)
    {
        bool duck_moved = false;
        for (int i = 0; i < columns - 1; ++i)
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
        total_rounds++;
    }
    output_file << total_rounds << endl;
    return 0;
}