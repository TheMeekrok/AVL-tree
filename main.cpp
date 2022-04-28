#include <bits/stdc++.h>

using namespace std;

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int height;
} Node;

void print(Node* node) {
    if (node) {
        print(node->left);
        cout << node->key << " " << node->height << endl;
        print(node->right);
    }
}

void print_2d(Node* node, int distance, int count) {
    if (!node) return;
    distance += count;

    print_2d(node->right, distance, count);
    cout << std::endl;
    for (int i = count; i < distance; i++)
        cout << " ";
    cout << node->key << " (" << node->height << ")" << endl;
    print_2d(node->left, distance, count);
}

int height(Node* node) {
    if (!node) return 0;
    return node->height;
}

Node* new_node(Node* node, int key) {
    node = new Node;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;

    return node;
}

int get_balance(Node* node) {
    if (!node)
        return 0;
    return height(node->left) - height(node->right);
}

Node* left_rotate(Node* x) {
    Node* y = x->left;
    Node* T = y->right;
    x->left = T;
    y->right = x;

    x->height = max(height(x->left), height(x->left)) + 1;
    y->height = max(height(y->left), height(y->left)) + 1;

    return y;
}

Node* right_rotate(Node* x) {
    Node* y = x->right;
    Node* T = y->left;
    x->right = T;
    y->left = x;

    x->height = max(height(x->left), height(x->left)) + 1;
    y->height = max(height(y->left), height(y->left)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return new_node(node, key);

    if (key > node->key)
        node->right = insert(node->right, key);
    else if (key < node->key)
        node->left = insert(node->left, key);
    else return node;

    node->height = max(height(node->right), height(node->left)) + 1;

    int balance = get_balance(node);
    if (balance > 1)
        return left_rotate(node);
    if (balance < -1)
        return right_rotate(node);

    return node;
}

int main() {
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    print_2d(root, 0, 10);
    return 0;
}
