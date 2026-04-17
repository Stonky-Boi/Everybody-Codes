#include <iostream>
#include <fstream>
using namespace std;

int get_potion(char creature)
{
    if (creature == 'A')
        return 0;
    if (creature == 'B')
        return 1;
    if (creature == 'C')
        return 3;
    return 0;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string creatures;
    input_file >> creatures;
    long long potions = 0;
    for (char c : creatures)
        potions += get_potion(c);
    output_file << potions;
    return 0;
}