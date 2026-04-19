#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct BIT
{
    int n;
    vector<int> tree;
    int msb;

    BIT(int size) : n(size), tree(size + 1, 0)
    {
        msb = 1;
        while (msb * 2 <= n)
            msb *= 2;
    }

    void add(int i, int delta)
    {
        for (; i <= n; i += i & -i)
            tree[i] += delta;
    }

    int find(int k)
    {
        int position = 0;
        for (int i = msb; i > 0; i /= 2)
        {
            if (position + i <= n && tree[position + i] < k)
            {
                position += i;
                k -= tree[position];
            }
        }
        return position + 1;
    }
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    string base_balloons = "";
    while (getline(input_file, line))
        base_balloons += line;
    string balloons = "";
    for (int i = 0; i < 100; i++)
        balloons += base_balloons;
    int n = balloons.length();
    BIT bit(n);
    for (int i = 1; i <= n; i++)
        bit.add(i, 1);
    int size = n;
    long long shots = 0;
    int bolt_index = 0;
    char bolt_sequence[] = {'R', 'G', 'B'};
    while (size > 0)
    {
        char bolt = bolt_sequence[bolt_index % 3];
        bolt_index++;
        shots++;
        int first = bit.find(1);
        char target = balloons[first - 1];
        bool is_match = (target == bolt);
        bit.add(first, -1);
        int old_size = size;
        size--;
        if (is_match && (old_size % 2 == 0))
        {
            int opp_k = old_size / 2;
            int opp_position = bit.find(opp_k);
            bit.add(opp_position, -1);
            size--;
        }
    }
    output_file << shots;
    return 0;
}