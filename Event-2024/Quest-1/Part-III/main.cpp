#include <iostream>
#include <fstream>
using namespace std;

int get_potion(char creature)
{
    if (creature == 'A')
        return 0;
    if (creature == 'B')
        return 1;
    if (creature == 'C')
        return 3;
    if (creature == 'D')
        return 5;
    return 0;
}

void process_creature(const string &creatures, size_t index, int &monsters, long long &group_potions)
{
    if (index < creatures.length() && creatures[index] != 'x')
    {
        monsters++;
        group_potions += get_potion(creatures[index]);
    }
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string creatures;
    input_file >> creatures;
    long long potions = 0;
    for (size_t i = 0; i < creatures.length(); i += 3)
    {
        int monsters = 0;
        long long group_potions = 0;
        process_creature(creatures, i, monsters, group_potions);
        process_creature(creatures, i + 1, monsters, group_potions);
        process_creature(creatures, i + 2, monsters, group_potions);
        if (monsters == 2)
            group_potions += 2;
        else if (monsters == 3)
            group_potions += 6;
        potions += group_potions;
    }
    output_file << potions;
    return 0;
}