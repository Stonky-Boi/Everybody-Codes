#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
using namespace std;

struct Node
{
    int id;
    int rank;
    char symbol;
    Node *left;
    Node *right;

    Node(int i, int r, char s)
    {
        id = i;
        rank = r;
        symbol = s;
        left = nullptr;
        right = nullptr;
    }
};

Node *insert(Node *root, int id, int rank, char symbol)
{
    if (root == nullptr)
        return new Node(id, rank, symbol);
    if (rank < root->rank)
        root->left = insert(root->left, id, rank, symbol);
    else if (rank > root->rank)
        root->right = insert(root->right, id, rank, symbol);
    return root;
}

Node *find(Node *root, int target_id)
{
    if (root == nullptr)
        return nullptr;
    if (root->id == target_id)
        return root;
    Node *left_res = find(root->left, target_id);
    if (left_res != nullptr)
        return left_res;
    return find(root->right, target_id);
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
        stringstream ss(line);
        string command;
        ss >> command;
        if (command == "ADD")
        {
            int id, l_rank, r_rank;
            char l_symbol, r_symbol, comma;
            ss.ignore(4);
            ss >> id;
            ss.ignore(7);
            ss >> l_rank >> comma >> l_symbol;
            ss.ignore(9);
            ss >> r_rank >> comma >> r_symbol;
            left_root = insert(left_root, id, l_rank, l_symbol);
            right_root = insert(right_root, id, r_rank, r_symbol);
        }
        else if (command == "SWAP")
        {
            int target_id;
            ss >> target_id;
            Node *left_node = find(left_root, target_id);
            Node *right_node = find(right_root, target_id);
            if (left_node != nullptr && right_node != nullptr)
            {
                int temp_rank = left_node->rank;
                char temp_symbol = left_node->symbol;
                left_node->rank = right_node->rank;
                left_node->symbol = right_node->symbol;
                right_node->rank = temp_rank;
                right_node->symbol = temp_symbol;
            }
        }
    }
    string left_message = max_level_message(left_root);
    string right_message = max_level_message(right_root);
    output_file << left_message << right_message;
    return 0;
}