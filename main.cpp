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

Node* left_rotate(Node* node) {

}

Node* right_rotate(Node* node) {

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
    if (balance > 1) {

    }

    return node;
}

int main() {
    Node* root = nullptr;
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 0);

    //print(root);
    return 0;
}
