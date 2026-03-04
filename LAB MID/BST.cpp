#include <iostream>
#include <string>
using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node *left;
        Node *right;
    };

    Node *root;

    // ==========================================
    // PRIVATE HELPER FUNCTIONS
    // ==========================================

    Node* createNode(T val) {
        Node* newNode = new Node;
        newNode->data = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    Node* bst_insert(Node *btNode, T val) {
        if (btNode == nullptr) {
            return createNode(val);
        }

        // Note: Custom classes (like Machine) must overload <= and > operators
        if (val <= btNode->data) {
            btNode->left = bst_insert(btNode->left, val);
        }
        else {
            btNode->right = bst_insert(btNode->right, val);
        }
        return btNode;
    }

    Node* findMin(Node *node) {
        Node *current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* bst_delete(Node *rootNode, T val) {
        if (rootNode == nullptr) return nullptr;

        if (val < rootNode->data) {
            rootNode->left = bst_delete(rootNode->left, val);
        }
        else if (val > rootNode->data) {
            rootNode->right = bst_delete(rootNode->right, val);
        }
        else {
            // Case 1 & 2: No child or One child
            if (rootNode->left == nullptr) {
                Node *temp = rootNode->right;
                delete rootNode;
                return temp;
            }
            else if (rootNode->right == nullptr) {
                Node *temp = rootNode->left;
                delete rootNode;
                return temp;
            }
            // Case 3: Two children
            Node *temp = findMin(rootNode->right);
            rootNode->data = temp->data;
            rootNode->right = bst_delete(rootNode->right, temp->data);
        }
        return rootNode;
    }

    void inorder(Node *node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    bool searchNode(Node *node, T val) {
        if (node == nullptr) return false;
        if (node->data == val) return true;
        
        if (val < node->data) 
            return searchNode(node->left, val);
        else 
            return searchNode(node->right, val);
    }

    void freeTree(Node *node) {
        if (node) {
            freeTree(node->left);
            freeTree(node->right);
            delete node;
        }
    }

    // Deep Copy Helper
    Node* copyTree(Node *node) {
        if (node == nullptr) return nullptr;
        Node *newNode = createNode(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

public:
    BST() { root = nullptr; }
    
    ~BST() {
        freeTree(root); 
        root = nullptr; 
    }

    void insert(T val) { root = bst_insert(root, val); }
    void remove(T val) { root = bst_delete(root, val); }
    void inorder()   { inorder(root); cout << endl; }
    bool search(T val) { return searchNode(root, val); }
    bool isEmpty() { return (root == nullptr); }

    // Returns a new BST object (Deep Copy)
    BST<T> copy() {
        BST<T> newTree;
        newTree.root = copyTree(root);
        return newTree;
    }
};

/*
    bool operator<=(const Class& other) const { return n <= other.id; }
    bool operator>(const Class& other) const { return n > other.id; }
    bool operator<(const Class& other) const { return n < other.id; }
    bool operator==(const Class& other) const { return id == other.id; }

        friend ostream& operator<<(ostream& os, const struct& r) {
        -----------------------
        return os;
        }

    */