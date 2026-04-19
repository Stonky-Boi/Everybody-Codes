#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    long long sum = 0;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int x = 0, y = 0;
        size_t x_position = line.find("x=");
        size_t y_position = line.find("y=");
        if (x_position != string::npos && y_position != string::npos)
        {
            x = stoi(line.substr(x_position + 2, y_position - x_position - 2));
            y = stoi(line.substr(y_position + 2));
            int D = x + y - 1;
            int new_x = (x - 1 + 100) % D + 1;
            int new_y = D - new_x + 1;
            sum += new_x + 100LL * new_y;
        }
    }
    output_file << sum;
    return 0;
}