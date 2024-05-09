#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

Node* newNode(string key, string value) {
    Node* node = new Node;
    node->keyword = key;
    node->meaning = value;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node* insert(Node* node, string key, string value) {
    if (node == nullptr)
        return newNode(key, value);

    if (key < node->keyword)
        node->left = insert(node->left, key, value);
    else if (key > node->keyword)
        node->right = insert(node->right, key, value);
    else {
        cout << "Keyword already exists. Updating value." << endl;
        node->meaning = value;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->keyword)
        return rightRotate(node);

    if (balance < -1 && key > node->right->keyword)
        return leftRotate(node);

    if (balance > 1 && key > node->left->keyword) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->keyword) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, string key) {
    if (root == nullptr)
        return root;

    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        inorder(root->right);
    }
}

void reverseInorder(Node* root) {
    if (root != nullptr) {
        reverseInorder(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        reverseInorder(root->left);
    }
}

Node* search(Node* root, string key, int& comparisons) {
    comparisons++;
    if (root == nullptr || root->keyword == key)
        return root;

    if (root->keyword < key)
        return search(root->right, key, comparisons);
    return search(root->left, key, comparisons);
}

int main() {
    Node* root = nullptr;
    int choice;
    string keyword, meaning;
    int comparisons;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add New Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Meaning\n";
        cout << "4. Display in Ascending Order\n";
        cout << "5. Display in Descending Order\n";
        cout << "6. Find Keyword\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Keyword: ";
                cin >> keyword;
                cout << "Enter Meaning: ";
                cin >> meaning;
                root = insert(root, keyword, meaning);
                break;
            case 2:
                cout << "Enter Keyword to Delete: ";
                cin >> keyword;
                root = deleteNode(root, keyword);
                break;
            case 3:
                cout << "Enter Keyword to Update: ";
                cin >> keyword;
                cout << "Enter New Meaning: ";
                cin >> meaning;
                root = deleteNode(root, keyword);
                root = insert(root, keyword, meaning);
                break;
            case 4:
                cout << "Dictionary in Ascending Order:\n";
                inorder(root);
                break;
            case 5:
                cout << "Dictionary in Descending Order:\n";
                reverseInorder(root);
                break;
            case 6:
                cout << "Enter Keyword to Find: ";
                cin >> keyword;
                comparisons = 0;
                search(root, keyword, comparisons);
                if (comparisons > 0)
                    cout << "Number of Comparisons: " << comparisons << endl;
                else
                    cout << "Keyword not found." << endl;
                break;
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}