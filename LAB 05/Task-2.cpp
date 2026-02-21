#include <iostream>
#include <string>
using namespace std;

// --- Data Structures ---
struct Book {
    int id;
    string title;
    int pop;  // Popularity (Key)
};

struct node {
    Book data;
    node *left;
    node *right;
};

class Library {
private:
    node *root;

    // --- Helper: Create Node ---
    node* createNode(Book b) {
        node* newNode = new node;
        newNode->data = b;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // --- Helper: Insert (Recursive) ---
    node* bst_insert(node *btNode, Book b) {
        if(btNode == nullptr) {
            return createNode(b);
        }
        
        // Compare Popularity
        if(b.pop < btNode->data.pop) {
            btNode->left = bst_insert(btNode->left, b);
        }
        else {
            btNode->right = bst_insert(btNode->right, b);
        }
        return btNode;
    }

    // --- Helper: Count Nodes ---
    int count(node *r) {
        if(r == nullptr) return 0;
        return 1 + count(r->left) + count(r->right);
    }

    // --- Helper: Top K (Reverse Inorder: Right -> Root -> Left) ---
    void top_k(node *r, int k, int &cnt) {
        if(r == nullptr || cnt >= k) return;

        top_k(r->right, k, cnt); // Go Right 

        if(cnt < k) {
            cout << cnt+1 << ". " << r->data.title << " (" << r->data.pop << ")" << endl;
            cnt++;
        }

        if(cnt < k) top_k(r->left, k, cnt); // Go Left
    }

    // --- Helper: Range Query ---
    void range_q(node *r, int min, int max) {
        if(r == nullptr) return;

        if(r->data.pop > min) 
            range_q(r->left, min, max);

        if(r->data.pop >= min && r->data.pop <= max)
            cout << r->data.title << " (" << r->data.pop << ")" << endl;

        if(r->data.pop < max) 
            range_q(r->right, min, max);
    }

    // --- Helper: Free Memory ---
    void freeTree(node *r) {
        if(r) {
            freeTree(r->left);
            freeTree(r->right);
            delete r;
        }
    }

public:
    Library() { root = nullptr; }
    ~Library() { freeTree(root); }

    // --- Wrappers ---
    void insert(int id, string t, int p) {
        Book b = {id, t, p};
        root = bst_insert(root, b);
    }

    void countBooks() {
        cout << "Total: " << count(root) << endl;
    }

    void showTop(int k) {
        int c = 0;
        cout << "--- Top " << k << " ---" << endl;
        top_k(root, k, c);
    }

    void showRange(int min, int max) {
        cout << "--- Range " << min << "-" << max << " ---" << endl;
        range_q(root, min, max);
    }
    
};

int main() {
    Library lib;

    // Inserting dummy data
    lib.insert(1, "Harry Potter", 95);
    lib.insert(2, "Calculus", 20);
    lib.insert(3, "Dune", 90);
    lib.insert(4, "1984", 80);
    lib.insert(5, "Gatsby", 50);

    lib.countBooks();
    
    lib.showTop(3); // Should show 95, 90, 80
    
    lib.showRange(40, 85); // Should show 50, 80

    system("pause>0");
    return 0;
}