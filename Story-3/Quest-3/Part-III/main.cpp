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
    node *parent;
    bool left;
    int bond_type;

    node() : id(0), left_child(nullptr), right_child(nullptr), parent(nullptr), left(false), bond_type(0) {}
};

struct socket
{
    node *parent;
    bool left;
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

int check_bond(const string &plug, const string &socket)
{
    int plug_space = plug.find(' ');
    int socket_space = socket.find(' ');
    if (plug_space == string::npos || socket_space == string::npos)
        return plug == socket ? 2 : 0;
    string plug_color = plug.substr(0, plug_space);
    string plug_shape = plug.substr(plug_space + 1);
    string socket_color = socket.substr(0, socket_space);
    string socket_shape = socket.substr(socket_space + 1);
    bool color_match = (plug_color == socket_color);
    bool shape_match = (plug_shape == socket_shape);
    if (color_match && shape_match)
        return 2;
    if (color_match || shape_match)
        return 1;
    return 0;
}

socket next_socket_skip(socket curr, node *root)
{
    if (curr.left)
        return {curr.parent, false};
    else
    {
        node *p = curr.parent;
        while (p->parent != nullptr)
        {
            if (p->left)
                return {p->parent, false};
            p = p->parent;
        }
        return {root, true};
    }
}

void insert(node *root, node *new_node)
{
    socket curr = {root, true};
    while (true)
    {
        node *child = curr.left ? curr.parent->left_child : curr.parent->right_child;
        std::string socket_str = curr.left ? curr.parent->left_socket : curr.parent->right_socket;
        int bond = check_bond(new_node->plug, socket_str);
        if (child == nullptr)
        {
            if (bond > 0)
            {
                if (curr.left)
                    curr.parent->left_child = new_node;
                else
                    curr.parent->right_child = new_node;
                new_node->parent = curr.parent;
                new_node->left = curr.left;
                new_node->bond_type = bond;
                break;
            }
            else
                curr = next_socket_skip(curr, root);
        }
        else
        {
            if (bond == 2 && child->bond_type == 1)
            {
                node *displaced = child;
                if (curr.left)
                    curr.parent->left_child = new_node;
                else
                    curr.parent->right_child = new_node;
                new_node->parent = curr.parent;
                new_node->left = curr.left;
                new_node->bond_type = 2;
                new_node = displaced;
                curr = next_socket_skip(curr, root);
            }
            else
                curr = {child, true};
        }
    }
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