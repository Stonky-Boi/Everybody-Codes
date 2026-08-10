#include <iostream>
#include <fstream>
using namespace std;

struct complex_number
{
    int x;
    int y;
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
    int a_x = stoi(line.substr(bracket_open + 1, comma - bracket_open - 1));
    int a_y = stoi(line.substr(comma + 1, bracket_close - comma - 1));
    complex_number a = {a_x, a_y};
    complex_number r = {0, 0};
    complex_number divisor = {10, 10};
    for (int i = 0; i < 3; i++)
    {
        r = multiply(r, r);
        r = divide(r, divisor);
        r = add(r, a);
    }
    output_file << "[" << r.x << "," << r.y << "]" << endl;
    return 0;
}