#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

typedef __int128_t int128;

long long extended_gcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<long long> moduli;
    vector<long long> remainders;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        size_t x_position = line.find("x=");
        size_t y_position = line.find("y=");
        if (x_position != string::npos && y_position != string::npos)
        {
            long long x = stoll(line.substr(x_position + 2, y_position - x_position - 2));
            long long y = stoll(line.substr(y_position + 2));
            long long current_modulus = x + y - 1;
            long long target_remainder = y - 1;
            moduli.push_back(current_modulus);
            remainders.push_back(target_remainder);
        }
    }
    long long current_modulus = moduli[0];
    long long current_remainder = remainders[0];
    for (size_t i = 1; i < moduli.size(); i++)
    {
        long long next_modulus = moduli[i];
        long long next_remainder = remainders[i];
        long long u, v;
        long long gcd_value = extended_gcd(current_modulus, next_modulus, u, v);
        int128 lcm_value = (int128)current_modulus / gcd_value * next_modulus;
        int128 difference = next_remainder - current_remainder;
        int128 k1 = (int128)u * (difference / gcd_value);
        k1 %= (next_modulus / gcd_value);
        int128 new_remainder = current_remainder + k1 * current_modulus;
        new_remainder %= lcm_value;
        if (new_remainder < 0)
            new_remainder += lcm_value;
        current_modulus = (long long)lcm_value;
        current_remainder = (long long)new_remainder;
    }
    if (current_remainder == 0)
        current_remainder = current_modulus;
    output_file << current_remainder;
    return 0;
}