#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct number_range
{
    int start;
    int end;

    int length() const
    {
        if (start <= end)
            return end - start + 1;
        else
            return start - end + 1;
    }

    int get_forward(int i) const
    {
        if (start <= end)
            return start + i;
        else
            return start - i;
    }

    int get_backward(int i) const
    {
        if (start <= end)
            return end - i;
        else
            return end + i;
    }
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<number_range> forward;
    vector<number_range> backward;
    string line;
    forward.push_back({1, 1});
    int total_length = 1;
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
            number_range curr_range = {start, end};
            total_length += curr_range.length();
            if (i % 2 == 0)
                forward.push_back(curr_range);
            else
                backward.push_back(curr_range);
            i++;
        }
    }
    long long target = 202520252025LL;
    int final_position = target % total_length;
    for (int i = 0; i < forward.size(); i++)
    {
        if (final_position < forward[i].length())
        {
            output_file << forward[i].get_forward(final_position) << endl;
            return 0;
        }
        final_position -= forward[i].length();
    }
    for (auto it = backward.rbegin(); it != backward.rend(); it++)
    {
        if (final_position < it->length())
        {
            output_file << it->get_backward(final_position) << endl;
            return 0;
        }
        final_position -= it->length();
    }
    return 0;
}