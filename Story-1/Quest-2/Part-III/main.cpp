#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

struct Node
{
    int id;
    int rank;
    char symbol;
    Node *left;
    Node *right;
    Node *parent;

    Node(int i, int r, char s)
    {
        id = i;
        rank = r;
        symbol = s;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

Node *left_root = nullptr;
Node *right_root = nullptr;
vector<Node *> nodes_l(100000, nullptr);
vector<Node *> nodes_r(100000, nullptr);

void insert(Node *&root, Node *new_node)
{
    if (root == nullptr)
    {
        root = new_node;
        new_node->parent = nullptr;
        return;
    }
    Node *curr = root;
    while (true)
    {
        if (new_node->rank < curr->rank)
        {
            if (curr->left == nullptr)
            {
                curr->left = new_node;
                new_node->parent = curr;
                return;
            }
            curr = curr->left;
        }
        else if (new_node->rank > curr->rank)
        {
            if (curr->right == nullptr)
            {
                curr->right = new_node;
                new_node->parent = curr;
                return;
            }
            curr = curr->right;
        }
        else
            return;
    }
}

void swap(int id)
{
    Node *u = nodes_l[id];
    Node *v = nodes_r[id];
    if (u == nullptr || v == nullptr || u == v)
        return;
    Node *p_u = u->parent;
    Node *p_v = v->parent;
    bool u_is_l_root = (left_root == u);
    bool u_is_r_root = (right_root == u);
    bool v_is_l_root = (left_root == v);
    bool v_is_r_root = (right_root == v);
    if (p_u != nullptr)
    {
        if (p_u->left == u)
            p_u->left = v;
        else
            p_u->right = v;
    }
    if (p_v != nullptr)
    {
        if (p_v->left == v)
            p_v->left = u;
        else
            p_v->right = u;
    }
    if (u_is_l_root)
        left_root = v;
    else if (v_is_l_root)
        left_root = u;
    if (u_is_r_root)
        right_root = v;
    else if (v_is_r_root)
        right_root = u;
    u->parent = p_v;
    v->parent = p_u;
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
    while (getline(input_file, line))
    {
        if (line.empty())
            continue;
        if (line.find("ADD") == 0)
        {
            int id_pos = line.find("id=");
            int l_pos = line.find("left=[");
            int r_pos = line.find("right=[");
            int id = stoi(line.substr(id_pos + 3));
            int l_comma = line.find(',', l_pos);
            int l_rank = stoi(line.substr(l_pos + 6, l_comma - l_pos - 6));
            char l_sym = line[l_comma + 1];
            int r_comma = line.find(',', r_pos);
            int r_rank = stoi(line.substr(r_pos + 7, r_comma - r_pos - 7));
            char r_sym = line[r_comma + 1];
            Node *l_node = new Node(id, l_rank, l_sym);
            Node *r_node = new Node(id, r_rank, r_sym);
            if (id >= nodes_l.size())
            {
                nodes_l.resize(id + 1000, nullptr);
                nodes_r.resize(id + 1000, nullptr);
            }
            nodes_l[id] = l_node;
            nodes_r[id] = r_node;
            insert(left_root, l_node);
            insert(right_root, r_node);
        }
        else if (line.find("SWAP") == 0)
        {
            int id = stoi(line.substr(5));
            swap(id);
        }
    }
    string left_message = max_level_message(left_root);
    string right_message = max_level_message(right_root);
    output_file << left_message << right_message;
    return 0;
}