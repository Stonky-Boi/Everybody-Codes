#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct node
{
    int id;
    string plug;
    string left_socket;
    string right_socket;
    node *left_child;
    node *right_child;

    node() : id(0), left_child(nullptr), right_child(nullptr) {}
};

string get_field(const string &line, const string &prefix, const string &suffix)
{
    int start = line.find(prefix);
    if (start == string::npos)
        return "";
    start += prefix.length();
    int end = line.find(suffix, start);
    if (end == string::npos)
        return line.substr(start);
    return line.substr(start, end - start);
}

bool insert(node *current, node *new_node)
{
    if (current == nullptr)
        return false;
    if (current->left_child == nullptr)
    {
        if (current->left_socket == new_node->plug)
        {
            current->left_child = new_node;
            return true;
        }
    }
    else
    {
        if (insert(current->left_child, new_node))
            return true;
    }
    if (current->right_child == nullptr)
    {
        if (current->right_socket == new_node->plug)
        {
            current->right_child = new_node;
            return true;
        }
    }
    else
    {
        if (insert(current->right_child, new_node))
            return true;
    }
    return false;
}

void inorder(node *current, vector<int> &traversal)
{
    if (current == nullptr)
        return;
    inorder(current->left_child, traversal);
    traversal.push_back(current->id);
    inorder(current->right_child, traversal);
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    string line;
    vector<node *> all_nodes;
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        node *new_node = new node();
        new_node->id = stoi(get_field(line, "id=", ","));
        new_node->plug = get_field(line, "plug=", ",");
        new_node->left_socket = get_field(line, "leftSocket=", ",");
        new_node->right_socket = get_field(line, "rightSocket=", ",");
        all_nodes.push_back(new_node);
    }
    node *root = all_nodes[0];
    for (int i = 1; i < all_nodes.size(); i++)
        insert(root, all_nodes[i]);
    vector<int> tree;
    inorder(root, tree);
    int checksum = 0;
    for (int i = 0; i < tree.size(); i++)
        checksum += (i + 1) * tree[i];
    output_file << checksum << endl;
    for (node *pointer : all_nodes)
        delete pointer;
    return 0;
}