#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    int mentor_count = 0;
    int total_pairs = 0;
    for (char character : line)
    {
        if (character == 'A')
            mentor_count++;
        else if (character == 'a')
            total_pairs += mentor_count;
    }
    output_file << total_pairs << endl;
    return 0;
}