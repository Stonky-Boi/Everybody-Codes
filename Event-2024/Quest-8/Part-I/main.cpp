#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    long long blocks;
    if (input_file >> blocks)
    {
        long long layers = sqrt(blocks);
        while (layers * layers < blocks)
            layers++;
        long long missing = (layers * layers) - blocks;
        long long width = 2 * layers - 1;
        long long result = missing * width;
        output_file << result;
    }
    return 0;
}