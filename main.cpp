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
        cout << node->key << " ";
        print(node->right);
    }
}

void print_2d(Node* node, int distance, int count) {
    if (!node) return;
    distance += count;

    print_2d(node->right, distance, count);
    cout << endl;
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
    Node* y = x->right;
    Node* T = y->left;
    x->right = T;
    y->left = x;

    x->height = max(height(x->left), height(x->left)) + 1;
    y->height = max(height(y->left), height(y->left)) + 1;

    return y;
}

Node* right_rotate(Node* x) {
    Node* y = x->left;
    Node* T = y->right;
    x->left = T;
    y->right = x;

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
    if (balance < -1) {
        if (height(node->right->left) > height(node->right->right))
            node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    if (balance > 1) {
        if (height(node->left->right) > height(node->left->left))
            node->right = right_rotate(node->right);
        return right_rotate(node);
    }

    return node;
}

Node* min_node(Node* node) {
    while (node->left)
        node = node->left;
    return node;
}

Node* remove(Node* node, int key) {
    if (!node)
        return node;

    if (key < node->key)
        remove(node->left, key);
    else if (key > node->key)
        remove(node->right, key);
    else {
        //Если один или нет потомков
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;

            //Случай если нет потомков
            if (!temp) {
                temp = node;
                node = nullptr;
            }
            //Еcли есть, то присваиваем его текущему узлу
            else
                *node = *temp;

            //И очищаем память
            delete temp;
        }
        else if (node->left && node->right) {
            Node* temp = min_node(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    if (!node)
        return node;
    return node;
}

int main() {
    Node* root = nullptr;
    string user_in;

    while (cin >> user_in) {
        int key;
        if (user_in == "add") {
            cin >> key;
            root = insert(root, key);
        }
        if (user_in == "remove") {
            cin >> key;
            root = remove(root, key);
        }
        if (user_in == "min_node") {
            cout << min_node(root)->key << endl;
        }
        if (user_in == "print") {
            int num;
            cin >> num;
            switch (num) {
                case 1:
                    print(root);
                    cout << endl;
                    break;
                case 2:
                    print_2d(root, 0, 10);
                    break;
                default:
                    print(root);
                    break;
            }
        }
    }
    return 0;
}
