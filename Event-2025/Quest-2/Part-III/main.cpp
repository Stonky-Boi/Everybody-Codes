#include <iostream>
#include <fstream>
using namespace std;

struct complex_number
{
    long long x;
    long long y;
};

complex_number add(const complex_number &a, const complex_number &b)
{
    return {a.x + b.x, a.y + b.y};
}

complex_number multiply(const complex_number &a, const complex_number &b)
{
    return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}

complex_number divide(const complex_number &a, const complex_number &b)
{
    return {a.x / b.x, a.y / b.y};
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    getline(input_file, line);
    int bracket_open = line.find('[');
    int comma = line.find(',');
    int bracket_close = line.find(']');
    long long a_x = stoll(line.substr(bracket_open + 1, comma - bracket_open - 1));
    long long a_y = stoll(line.substr(comma + 1, bracket_close - comma - 1));
    complex_number divisor = {100000, 100000};
    int count = 0;
    for (int y_step = 0; y_step <= 1000; y_step++)
    {
        for (int x_step = 0; x_step <= 1000; x_step++)
        {
            complex_number p = {a_x + x_step, a_y + y_step};
            complex_number r = {0, 0};
            bool engrave = true;
            for (int cycle = 1; cycle <= 100; cycle++)
            {
                r = multiply(r, r);
                r = divide(r, divisor);
                r = add(r, p);
                if (r.x > 1000000 || r.x < -1000000 || r.y > 1000000 || r.y < -1000000)
                {
                    engrave = false;
                    break;
                }
            }
            if (engrave)
                count++;
        }
    }
    output_file << count << endl;
    return 0;
}