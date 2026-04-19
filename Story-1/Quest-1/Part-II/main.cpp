#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

string calculate_eni(long long n, long long exp, long long mod)
{
    long long start_exp = 1;
    if (exp >= 5)
        start_exp = exp - 4;
    long long curr = 1;
    long long base = n % mod;
    long long power = start_exp;
    while (power > 0)
    {
        if (power % 2 == 1)
            curr = (curr * base) % mod;
        base = (base * base) % mod;
        power /= 2;
    }
    vector<long long> rems;
    rems.push_back(curr);
    for (long long i = start_exp + 1; i <= exp; i++)
    {
        curr = (curr * n) % mod;
        rems.push_back(curr);
    }
    string params = "";
    for (int i = static_cast<int>(rems.size()) - 1; i >= 0; i--)
        params += to_string(rems[i]);
    size_t non_zero = 0;
    while (non_zero < params.length() - 1 && params[non_zero] == '0')
        non_zero++;
    return params.substr(non_zero);
}

string add_large_numbers(const string &curr_sum, const string &max_result)
{
    string params = "";
    int carry = 0;
    int i = static_cast<int>(curr_sum.length()) - 1;
    int j = static_cast<int>(max_result.length()) - 1;
    while (i >= 0 || j >= 0 || carry > 0)
    {
        int digit1 = 0;
        if (i >= 0)
            digit1 = curr_sum[i] - '0';
        int digit2 = 0;
        if (j >= 0)
            digit2 = max_result[j] - '0';
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        params = to_string(sum % 10) + params;
        i--;
        j--;
    }
    size_t non_zero = 0;
    while (non_zero < params.length() - 1 && params[non_zero] == '0')
        non_zero++;
    return params.substr(non_zero);
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string max_result = "0";
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
            string eni_a = calculate_eni(a, x, m);
            string eni_b = calculate_eni(b, y, m);
            string eni_c = calculate_eni(c, z, m);
            string curr_sum = add_large_numbers(eni_a, eni_b);
            curr_sum = add_large_numbers(curr_sum, eni_c);
            if (curr_sum.length() != max_result.length())
            {
                if (curr_sum.length() > max_result.length())
                    max_result = curr_sum;
            }
            else
            {
                bool is_greater = false;
                for (size_t i = 0; i < curr_sum.length(); ++i)
                {
                    if (curr_sum[i] != max_result[i])
                    {
                        if (curr_sum[i] > max_result[i])
                            is_greater = true;
                        break;
                    }
                }
                if (is_greater)
                    max_result = curr_sum;
            }
        }
    }
    output_file << max_result;
    return 0;
}