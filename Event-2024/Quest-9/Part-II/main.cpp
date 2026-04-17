#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<int> brightness;
    int b;
    while (input_file >> b)
        brightness.push_back(b);
    int max_value = 0;
    for (int v : brightness)
    {
        if (v > max_value)
            max_value = v;
    }
    vector<int> dp(max_value + 1, 1e9);
    dp[0] = 0;
    vector<int> stamps = {1, 3, 5, 10, 15, 16, 20, 24, 25, 30};
    for (int i = 1; i <= max_value; i++)
    {
        for (int stamp : stamps)
        {
            if (i >= stamp)
                dp[i] = min(dp[i], dp[i - stamp] + 1);
        }
    }
    long long beetles = 0;
    for (int v : brightness)
        beetles += dp[v];
    output_file << beetles;
    return 0;
}