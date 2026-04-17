#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string words_line;
    getline(input_file, words_line);
    words_line = words_line.substr(6);
    vector<string> words;
    string current_word = "";
    for (char c : words_line)
    {
        if (c == ',')
        {
            words.push_back(current_word);
            current_word = "";
        }
        else
            current_word += c;
    }
    if (!current_word.empty())
        words.push_back(current_word);
    long long total_words = 0;
    string text_line;
    while (getline(input_file, text_line))
    {
        if (text_line.empty())
            continue;
        for (string w : words)
        {
            size_t position = 0;
            while ((position = text_line.find(w, position)) != string::npos)
            {
                total_words++;
                position++;
            }
        }
    }
    output_file << total_words;
    return 0;
}