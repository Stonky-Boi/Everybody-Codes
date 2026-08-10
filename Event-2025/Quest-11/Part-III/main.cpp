#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct sequence_segment
{
    long long count;
    long long sum;
};

long long max_element(long long count, long long sum)
{
    long long base = sum / count;
    long long remainder = sum % count;
    if (remainder > 0)
        return base + 1;
    return base;
}

long long min_element(long long count, long long sum)
{
    return sum / count;
}

bool should_merge(const sequence_segment &left, const sequence_segment &right)
{
    if (left.sum * right.count >= right.sum * left.count)
        return true;
    if (max_element(left.count, left.sum) > min_element(right.count, right.sum))
        return true;
    return false;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    vector<long long> ducks;
    string line;
    long long total_sum = 0;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        long long curr_count = stoll(line);
        ducks.push_back(curr_count);
        total_sum += curr_count;
    }
    long long columns = ducks.size();
    long long target = total_sum / columns;
    vector<sequence_segment> stack;
    for (int i = 0; i < columns; i++)
    {
        sequence_segment curr_segment = {1, ducks[i]};
        while (stack.size() >= 1)
        {
            sequence_segment top_segment = stack.back();
            if (should_merge(top_segment, curr_segment))
            {
                stack.pop_back();
                curr_segment.count += top_segment.count;
                curr_segment.sum += top_segment.sum;
            }
            else
                break;
        }
        stack.push_back(curr_segment);
    }
    vector<long long> stable_state;
    for (const sequence_segment &segment : stack)
    {
        long long base_value = segment.sum / segment.count;
        long long remainder = segment.sum % segment.count;
        for (int j = 0; j < segment.count - remainder; j++)
            stable_state.push_back(base_value);
        for (int j = 0; j < remainder; j++)
            stable_state.push_back(base_value + 1);
    }
    long long prefix_initial = 0;
    long long prefix_stable = 0;
    long long prefix_final = 0;
    long long rounds_1 = 0;
    long long rounds_2 = 0;
    for (int i = 0; i < columns; i++)
    {
        prefix_initial += ducks[i];
        prefix_stable += stable_state[i];
        prefix_final += target;
        long long difference_1 = prefix_initial - prefix_stable;
        if (difference_1 > rounds_1)
            rounds_1 = difference_1;
        long long difference_2 = prefix_final - prefix_stable;
        if (difference_2 > rounds_2)
            rounds_2 = difference_2;
    }
    long long total_rounds = rounds_1 + rounds_2;
    output_file << total_rounds << endl;
    return 0;
}