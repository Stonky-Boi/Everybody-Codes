#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    int distance_limit = 1000;
    int repetitions = 1000;
    int string_length = line.length();
    int total_length = string_length * repetitions;
    int mentor_a = 0;
    int mentor_b = 0;
    int mentor_c = 0;
    int total_pairs = 0;
    int window = min(total_length - 1, distance_limit);
    for (int i = 0; i <= window; i++)
    {
        char c = line[i % string_length];
        if (c == 'A')
            mentor_a++;
        else if (c == 'B')
            mentor_b++;
        else if (c == 'C')
            mentor_c++;
    }
    for (int i = 0; i < total_length; i++)
    {
        if (i > 0)
        {
            int right = i + distance_limit;
            if (right < total_length)
            {
                char c = line[right % string_length];
                if (c == 'A')
                    mentor_a++;
                else if (c == 'B')
                    mentor_b++;
                else if (c == 'C')
                    mentor_c++;
            }
            int left = i - distance_limit - 1;
            if (left >= 0)
            {
                char c = line[left % string_length];
                if (c == 'A')
                    mentor_a--;
                else if (c == 'B')
                    mentor_b--;
                else if (c == 'C')
                    mentor_c--;
            }
        }
        char curr_novice = line[i % string_length];
        if (curr_novice == 'a')
            total_pairs += mentor_a;
        else if (curr_novice == 'b')
            total_pairs += mentor_b;
        else if (curr_novice == 'c')
            total_pairs += mentor_c;
    }
    output_file << total_pairs << endl;
    return 0;
}