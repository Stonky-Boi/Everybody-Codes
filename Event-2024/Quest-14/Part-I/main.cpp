#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    if (getline(input_file, line))
    {
        long long curr_height = 0;
        long long max_height = 0;
        stringstream ss(line);
        string step;
        while (getline(ss, step, ','))
        {
            if (step.empty())
                continue;
            char direction = step[0];
            int distance = stoi(step.substr(1));
            if (direction == 'U')
            {
                curr_height += distance;
                if (curr_height > max_height)
                    max_height = curr_height;
            }
            else if (direction == 'D')
                curr_height -= distance;
        }
        output_file << max_height;
    }
    return 0;
}