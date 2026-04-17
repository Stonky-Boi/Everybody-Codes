#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

long long get_min_score(int x_c, int y_c)
{
    long long min_score = -1;
    for (int segment = 0; segment <= 2; segment++)
    {
        int multiplier = segment + 1;
        if (y_c == segment + x_c)
        {
            int power = max(1, x_c);
            long long score = 1LL * power * multiplier;
            if (min_score == -1 || score < min_score)
                min_score = score;
        }
        int power_phase2 = y_c - segment;
        if (power_phase2 >= 1 && power_phase2 < x_c && x_c <= 2 * power_phase2)
        {
            long long score = 1LL * power_phase2 * multiplier;
            if (min_score == -1 || score < min_score)
                min_score = score;
        }
        if ((y_c - segment + x_c) % 3 == 0)
        {
            int power_phase3 = (y_c - segment + x_c) / 3;
            if (power_phase3 >= 1 && x_c > 2 * power_phase3)
            {
                long long score = 1LL * power_phase3 * multiplier;
                if (min_score == -1 || score < min_score)
                    min_score = score;
            }
        }
    }
    return min_score;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    long long ranking = 0;
    int start_x, start_y;
    while (input_file >> start_x >> start_y)
    {
        long long best_score = -1;
        int max_xc = start_x / 2;
        int min_xc = max(0, start_x - start_y);
        for (int x_c = max_xc; x_c >= min_xc; x_c--)
        {
            int y_c = start_y - start_x + x_c;
            long long score = get_min_score(x_c, y_c);
            if (score != -1)
            {
                best_score = score;
                break;
            }
        }
        if (best_score != -1)
            ranking += best_score;
    }
    output_file << ranking;
    return 0;
}