#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

long long get_blocks(long long n, long long priests, long long acolytes)
{
    if (n == 1)
        return 1;
    vector<long long> T(n + 1);
    T[1] = 1;
    for (int i = 2; i <= n; i++)
        T[i] = (T[i - 1] * priests) % acolytes + acolytes;
    long long width = 2LL * n - 1;
    long long current_h = T[n];
    long long total_blocks = 2LL * current_h;
    for (int d = n - 2; d >= 1; d--)
    {
        current_h += T[d + 1];
        long long remove = ((priests % acolytes) * (width % acolytes) % acolytes * (current_h % acolytes)) % acolytes;
        total_blocks += 2LL * (current_h - remove);
    }
    current_h += T[1];
    long long remove = ((priests % acolytes) * (width % acolytes) % acolytes * (current_h % acolytes)) % acolytes;
    total_blocks += current_h - remove;
    return total_blocks;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    long long priests;
    if (input_file >> priests)
    {
        long long acolytes = 10;
        long long available_blocks = 202400000;
        long long left = 1;
        long long right = 1000000;
        long long best_layers = -1;
        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            if (get_blocks(mid, priests, acolytes) >= available_blocks)
            {
                best_layers = mid;
                right = mid - 1;
            }
            else
                left = mid + 1;
        }
        long long result = get_blocks(best_layers, priests, acolytes) - available_blocks;
        output_file << result;
    }
    return 0;
}