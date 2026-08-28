#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    int total_sum = 0;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        set<int> visited;
        int curr_position = 0;
        visited.insert(curr_position);
        int position = 0;
        while (position < line.length())
        {
            int comma = line.find(',', position);
            if (comma == string::npos)
                comma = line.length();
            string token = line.substr(position, comma - position);
            if (token.empty())
            {
                position = comma + 1;
                continue;
            }
            int jump_length = stoi(token);
            int next_position = curr_position - jump_length;
            if (next_position > 0 && visited.find(next_position) == visited.end())
                curr_position = next_position;
            else
            {
                curr_position += jump_length;
                while (visited.find(curr_position) != visited.end())
                    curr_position++;
            }
            visited.insert(curr_position);
            position = comma + 1;
        }
        total_sum += curr_position;
    }
    output_file << total_sum << endl;
    return 0;
}