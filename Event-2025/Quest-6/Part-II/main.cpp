#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    int mentor_a = 0;
    int mentor_b = 0;
    int mentor_c = 0;
    int total_pairs = 0;
    for (char character : line)
    {
        if (character == 'A')
            mentor_a++;
        else if (character == 'B')
            mentor_b++;
        else if (character == 'C')
            mentor_c++;
        else if (character == 'a')
            total_pairs += mentor_a;
        else if (character == 'b')
            total_pairs += mentor_b;
        else if (character == 'c')
            total_pairs += mentor_c;
    }
    output_file << total_pairs << endl;
    return 0;
}