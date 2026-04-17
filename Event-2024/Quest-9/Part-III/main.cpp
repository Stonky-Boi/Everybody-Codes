#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<int> dp(100005, 1e9);
    dp[0] = 0;
    vector<int> stamps = {1, 3, 5, 10, 15, 16, 20, 24, 25, 30, 37, 38, 49, 50, 74, 75, 100, 101};
    for (int i = 1; i <= 100000; i++)
    {
        for (int s : stamps)
        {
            if (i >= s)
                dp[i] = min(dp[i], dp[i - s] + 1);
        }
    }
    long long beetles = 0;
    long long brightness;
    while (input_file >> brightness)
    {
        long long min_current = 2e18;
        long long start = max(0LL, (brightness - 100 + 1) / 2);
        long long end = (brightness + 100) / 2;
        for (long long b1 = start; b1 <= end; ++b1)
        {
            long long b2 = brightness - b1;
            long long current_stamps = dp[b1] + dp[b2];
            if (current_stamps < min_current)
                min_current = current_stamps;
        }
        beetles += min_current;
    }
    output_file << beetles;
    return 0;
}