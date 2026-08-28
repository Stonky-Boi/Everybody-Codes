#include <iostream>
#include <fstream>
#include <set>
#include <utility>
using namespace std;

pair<int, int> parse_coordinates(const string &s)
{
    int bracket1 = s.find('[');
    int comma = s.find(',');
    int bracket2 = s.find(']');
    int x = stoi(s.substr(bracket1 + 1, comma - bracket1 - 1));
    int y = stoi(s.substr(comma + 1, bracket2 - comma - 1));
    return {x, y};
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    pair<int, int> start, a, b, c;
    string moves;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (line.find("START=") == 0)
            start = parse_coordinates(line);
        else if (line.find("A=") == 0)
            a = parse_coordinates(line);
        else if (line.find("B=") == 0)
            b = parse_coordinates(line);
        else if (line.find("C=") == 0)
            c = parse_coordinates(line);
        else
            moves = line.substr(6);
    }
    set<pair<int, int>> beetles;
    pair<int, int> curr = start;
    beetles.insert(curr);
    for (int i = 0; i < moves.length(); ++i)
    {
        char move = moves[i];
        pair<int, int> target;
        if (move == 'A')
            target = a;
        else if (move == 'B')
            target = b;
        else if (move == 'C')
            target = c;
        else
            continue;
        curr.first = (curr.first + target.first) / 2;
        curr.second = (curr.second + target.second) / 2;
        beetles.insert(curr);
    }
    set<pair<int, int>> fireflies;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    for (auto [x, y] : beetles)
    {
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            pair<int, int> neighbor = {nx, ny};
            if (beetles.find(neighbor) == beetles.end())
                fireflies.insert(neighbor);
        }
    }
    output_file << fireflies.size() << endl;
    return 0;
}