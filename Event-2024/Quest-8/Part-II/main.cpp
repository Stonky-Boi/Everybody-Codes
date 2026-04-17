#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    long long priests;
    if (input_file >> priests)
    {
        long long acolytes = 1111;
        long long available_blocks = 20240000;
        long long thickness = 1, width = 1;
        long long total_blocks = 0;
        while (true)
        {
            long long needed = width * thickness;
            total_blocks += needed;
            if (total_blocks >= available_blocks)
            {
                long long missing = total_blocks - available_blocks;
                long long result = missing * width;
                output_file << result;
                break;
            }
            width += 2;
            thickness = (thickness * priests) % acolytes;
        }
    }
    return 0;
}