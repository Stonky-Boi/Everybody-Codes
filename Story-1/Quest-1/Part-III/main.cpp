#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

long long calculate_eni(long long n, long long exp, long long mod)
{
    vector<long long> history;
    vector<long long> visited(mod, -1);
    long long current = 1;
    long long total_sum = 0;
    for (long long i = 0; i < exp; i++)
    {
        current = (current * n) % mod;
        if (visited[current] != -1)
        {
            long long cycle_start = visited[current];
            long long cycle_length = i - cycle_start;
            long long remaining_steps = exp - i;
            long long full_cycles = remaining_steps / cycle_length;
            long long remainder_steps = remaining_steps % cycle_length;
            long long cycle_sum = 0;
            for (long long j = cycle_start; j < i; j++)
                cycle_sum += history[j];
            total_sum += full_cycles * cycle_sum;
            for (long long j = 0; j < remainder_steps; j++)
                total_sum += history[cycle_start + j];
            return total_sum;
        }
        visited[current] = i;
        history.push_back(current);
        total_sum += current;
    }
    return total_sum;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    long long max_result = 0;
    string line;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        vector<long long> params;
        long long current_number = 0;
        bool parsing_number = false;
        for (char ch : line)
        {
            if (ch >= '0' && ch <= '9')
            {
                current_number = current_number * 10 + (ch - '0');
                parsing_number = true;
            }
            else if (parsing_number)
            {
                params.push_back(current_number);
                current_number = 0;
                parsing_number = false;
            }
        }
        if (parsing_number)
            params.push_back(current_number);
        if (params.size() == 7)
        {
            long long a = params[0];
            long long b = params[1];
            long long c = params[2];
            long long x = params[3];
            long long y = params[4];
            long long z = params[5];
            long long m = params[6];
            long long eni_a = calculate_eni(a, x, m);
            long long eni_b = calculate_eni(b, y, m);
            long long eni_c = calculate_eni(c, z, m);
            long long curr_sum = eni_a + eni_b + eni_c;
            if (curr_sum > max_result)
                max_result = curr_sum;
        }
    }
    output_file << max_result;
    return 0;
}