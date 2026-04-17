#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

long long gcd(long long a, long long b)
{
    while (b)
    {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

long long lcm(long long a, long long b)
{
    return (a / gcd(a, b)) * b;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    vector<int> advances;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ','))
        advances.push_back(stoi(token));
    int num_wheels = advances.size();
    vector<vector<string>> wheels(num_wheels);
    getline(input_file, line); // skip empty line
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        for (int i = 0; i < num_wheels; ++i)
        {
            if (i * 4 < line.length())
            {
                int length = min(3, (int)line.length() - i * 4);
                string symbol = line.substr(i * 4, length);
                if (symbol.length() >= 3 && symbol != "   ")
                {
                    string eyes = "";
                    eyes += symbol[0];
                    eyes += symbol[2];
                    wheels[i].push_back(eyes);
                }
            }
        }
    }
    long long period = 1;
    for (int i = 0; i < num_wheels; ++i)
    {
        long long wheel_length = wheels[i].size();
        long long advance = advances[i];
        long long p = wheel_length / gcd(wheel_length, advance);
        period = lcm(period, p);
    }
    long long cycle_coins = 0;
    for (long long t = 1; t <= period; ++t)
    {
        int freq[256] = {0};
        for (int i = 0; i < num_wheels; ++i)
        {
            long long idx = (t * advances[i]) % wheels[i].size();
            freq[wheels[i][idx][0]]++;
            freq[wheels[i][idx][1]]++;
        }
        for (int i = 0; i < 256; ++i)
        {
            if (freq[i] >= 3)
                cycle_coins += freq[i] - 2;
        }
    }
    long long total_pulls = 202420242024LL;
    long long full_cycles = total_pulls / period;
    long long remainder_pulls = total_pulls % period;
    long long remainder_coins = 0;
    for (long long t = 1; t <= remainder_pulls; ++t)
    {
        int freq[256] = {0};
        for (int i = 0; i < num_wheels; ++i)
        {
            long long idx = (t * advances[i]) % wheels[i].size();
            freq[wheels[i][idx][0]]++;
            freq[wheels[i][idx][1]]++;
        }
        for (int i = 0; i < 256; ++i)
        {
            if (freq[i] >= 3)
                remainder_coins += freq[i] - 2;
        }
    }
    long long total_coins = (full_cycles * cycle_coins) + remainder_coins;
    output_file << total_coins;
    return 0;
}