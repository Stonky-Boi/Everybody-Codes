#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void get_counts(long long N, const string &seq, long long counts[2][2][2])
{
    long long L = seq.length();
    if (L == 0)
        return;
    long long T = 0;
    long long S_T = 0;
    for (long long i = 1; i <= 4 * L; ++i)
    {
        long long h_next = seq[i % L] - '0';
        S_T = S_T ^ (h_next == 0);
        if (i % L == 0 && i % 2 == 0 && S_T == 0)
        {
            T = i;
            break;
        }
    }
    long long period_counts[2][2][2] = {0};
    long long S = 0;
    for (long long r = 0; r < T; ++r)
    {
        long long h_curr = seq[r % L] - '0';
        long long h_next = seq[(r + 1) % L] - '0';
        if (h_curr == h_next)
            period_counts[r % 2][h_curr][S]++;
        S = S ^ (h_next == 0);
    }
    long long full_periods = N / T;
    long long remainder = N % T;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                counts[i][j][k] = full_periods * period_counts[i][j][k];
    S = 0;
    for (long long r = 0; r < remainder; ++r)
    {
        long long h_curr = seq[r % L] - '0';
        long long h_next = seq[(r + 1) % L] - '0';
        if (h_curr == h_next)
            counts[r % 2][h_curr][S]++;
        S = S ^ (h_next == 0);
    }
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    long long width = 0;
    long long height = 0;
    string h_offset = "";
    string v_offset = "";
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (line.find("width=") == 0)
            width = stoll(line.substr(6));
        else if (line.find("height=") == 0)
            height = stoll(line.substr(7));
        else if (line.find("horizontal-offsets=") == 0)
            h_offset = line.substr(19);
        else if (line.find("vertical-offsets=") == 0)
            v_offset = line.substr(17);
    }
    long long row_counts[2][2][2] = {0};
    long long col_counts[2][2][2] = {0};
    get_counts(height, h_offset, row_counts);
    get_counts(width, v_offset, col_counts);
    long long total_color[2] = {0, 0};
    for (int rp = 0; rp < 2; ++rp)
    {
        for (int hv = 0; hv < 2; ++hv)
        {
            for (int sh = 0; sh < 2; ++sh)
            {
                for (int cp = 0; cp < 2; ++cp)
                {
                    for (int vv = 0; vv < 2; ++vv)
                    {
                        for (int sv = 0; sv < 2; ++sv)
                        {
                            if (cp == hv && rp == vv)
                            {
                                int color = sh ^ sv ^ (rp * cp);
                                long long combinations = row_counts[rp][hv][sh] * col_counts[cp][vv][sv];
                                total_color[color] += combinations;
                            }
                        }
                    }
                }
            }
        }
    }
    long long larger_group = max(total_color[0], total_color[1]);
    output_file << larger_group << endl;
    return 0;
}