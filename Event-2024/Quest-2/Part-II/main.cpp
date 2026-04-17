#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void mark_occurrences(const string &text_line, const string &word, vector<bool> &is_runic)
{
    size_t position = 0;
    while ((position = text_line.find(word, position)) != string::npos)
    {
        for (size_t i = 0; i < word.length(); i++)
            is_runic[position + i] = true;
        position++;
    }
}

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
    long long total_symbols = 0;
    string text_line;
    while (getline(input_file, text_line))
    {
        if (text_line.empty())
            continue;
        vector<bool> is_runic(text_line.length(), false);
        for (string w : words)
        {
            mark_occurrences(text_line, w, is_runic);
            string r = w;
            reverse(r.begin(), r.end());
            mark_occurrences(text_line, r, is_runic);
        }
        for (bool b : is_runic)
        {
            if (b)
                total_symbols++;
        }
    }
    output_file << total_symbols;
    return 0;
}