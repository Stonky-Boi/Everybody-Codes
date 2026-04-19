#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string balloons;
    string line;
    while (getline(input_file, line))
    {
        if (!line.empty())
            balloons += line;
    }
    int shots = 0;
    int bolt_index = 0;
    int position = 0;
    char bolt_sequence[] = {'R', 'G', 'B'};
    int n = balloons.length();
    while (position < n)
    {
        char bolt = bolt_sequence[bolt_index % 3];
        shots++;
        bolt_index++;
        while (position < n)
        {
            char balloon = balloons[position];
            position++;
            if (balloon != bolt)
                break;
        }
    }
    output_file << shots;
    return 0;
}