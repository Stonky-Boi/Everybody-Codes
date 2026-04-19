#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
using namespace std;

struct Node
{
    int rank;
    char symbol;
    Node *left;
    Node *right;

    Node(int r, char s)
    {
        rank = r;
        symbol = s;
        left = nullptr;
        right = nullptr;
    }
};

Node *insert(Node *root, int rank, char symbol)
{
    if (root == nullptr)
        return new Node(rank, symbol);
    if (rank < root->rank)
        root->left = insert(root->left, rank, symbol);
    else if (rank > root->rank)
        root->right = insert(root->right, rank, symbol);
    return root;
}

string max_level_message(Node *root)
{
    if (root == nullptr)
        return "";
    queue<Node *> q;
    q.push(root);
    int max_nodes = 0;
    string best_message = "";
    while (!q.empty())
    {
        int level_size = q.size();
        string current_message = "";
        for (int i = 0; i < level_size; i++)
        {
            Node *current = q.front();
            q.pop();
            current_message += current->symbol;
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }
        if (level_size > max_nodes)
        {
            max_nodes = level_size;
            best_message = current_message;
        }
    }
    return best_message;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    Node *left_root = nullptr;
    Node *right_root = nullptr;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        int id, l_rank, r_rank;
        char l_symbol, r_symbol, comma;
        string command;
        stringstream ss(line);
        ss >> command;
        ss.ignore(4);
        ss >> id;
        ss.ignore(7);
        ss >> l_rank >> comma >> l_symbol;
        ss.ignore(9);
        ss >> r_rank >> comma >> r_symbol;
        left_root = insert(left_root, l_rank, l_symbol);
        right_root = insert(right_root, r_rank, r_symbol);
    }
    string left_message = max_level_message(left_root);
    string right_message = max_level_message(right_root);
    output_file << left_message << right_message;
    return 0;
}