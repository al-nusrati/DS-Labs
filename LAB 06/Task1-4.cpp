#include <iostream>
#include <algorithm> // max()
using namespace std;

// --- 1. Node Structure ---
struct node {
    int data;
    node *left;
    node *right;
};

// --- 2. BST Class Definition ---
class BST {
private:
    node *root;

    // ==========================================
    // PRIVATE HELPER FUNCTIONS
    // ==========================================

    // --- Create a new node ---
    node* createNode(int val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // --- Recursive Insert (Task 1 Core) ---
    node* bst_insert(node *btNode, int val) {
        if (btNode == nullptr) {
            return createNode(val);
        }
        if (val <= btNode->data) {
            btNode->left = bst_insert(btNode->left, val);
        }
        else {
            btNode->right = bst_insert(btNode->right, val);
        }
        return btNode;
    }

    // --- Task 1 Helper: Construct from Array Recursively ---
    // Recursively iterates through array index to insert elements
    void constructArrayRec(int arr[], int n, int index) {
        if (index >= n) return; // Base case
        
        root = bst_insert(root, arr[index]); // Insert current
        constructArrayRec(arr, n, index + 1); // Recurse for next
    }

    // --- Task 2: Recursive Search ---
    // Returns true if found, false otherwise
    bool searchRec(node *r, int val) {
        if (r == nullptr) return false;      // Base case: Not found
        if (r->data == val) return true;     // Base case: Found

        if (val < r->data)
            return searchRec(r->left, val);  // Go Left
        else
            return searchRec(r->right, val); // Go Right
    }

    // --- Task 3: Calculate Height Recursively ---
    int heightRec(node *r) {
        if (r == nullptr) return -1; // Base case: Empty tree height is -1 (or 0 depending on convention)
        
        int leftH = heightRec(r->left);
        int rightH = heightRec(r->right);
        
        return max(leftH, rightH) + 1;
    }

    // --- Task 4a: Find Smallest Recursively ---
    int findSmallestRec(node *r) {
        if (r == nullptr) return -1; // Error code
        if (r->left == nullptr) return r->data; // Base case: Leftmost node
        return findSmallestRec(r->left);
    }

    // --- Task 4b: Find Largest Recursively ---
    int findLargestRec(node *r) {
        if (r == nullptr) return -1; // Error code
        if (r->right == nullptr) return r->data; // Base case: Rightmost node
        return findLargestRec(r->right);
    }

    // --- Standard Traversals ---
    void inorder(node *root) {
        if (root) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    // --- Free Memory ---
    void freeTree(node *root) {
        if (root) {
            freeTree(root->left);
            freeTree(root->right);
            delete root;
        }
    }

public:
    // ==========================================
    // PUBLIC INTERFACE
    // ==========================================
    
    BST() { root = nullptr; }
    
    ~BST() { 
        freeTree(root); 
        root = nullptr; 
    }

    // --- Task 1 ---
    void buildFromArray(int arr[], int n) {
        // Reset tree if needed, or just append
        constructArrayRec(arr, n, 0);
    }

    // --- Task 2 ---
    void search(int val) {
        if (searchRec(root, val))
            cout << "Value " << val << " FOUND in BST." << endl;
        else
            cout << "Value " << val << " NOT found." << endl;
    }

    // --- Task 3 ---
    void showHeight() {
        cout << "Height of BST: " << heightRec(root) << endl;
    }

    // --- Task 4 ---
    void showMinMax() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        cout << "Smallest Element: " << findSmallestRec(root) << endl;
        cout << "Largest Element: " << findLargestRec(root) << endl;
    }

    void insert(int val) { root = bst_insert(root, val); }
    void inorder() { inorder(root); cout << endl; }
};


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkedList {
public:
    // --- Task 5: Reverse Nodes in k-Group (Recursive) ---
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 1. Check if k nodes exist
        ListNode* cursor = head;
        for(int i = 0; i < k; i++){
            if(cursor == nullptr) return head; // Base case: Not enough nodes
            cursor = cursor->next;
        }

        // 2. Reverse k nodes
        ListNode* curr = head;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        
        for(int i = 0; i < k; i++){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // 3. Recursive call for the rest
        head->next = reverseKGroup(curr, k);

        return prev; // New head
    }

    // Helper to print list
    void printList(ListNode* head) {
        while(head) {
            cout << head->val << " -> ";
            head = head->next;
        }
        cout << "NULL" << endl;
    }
};



int main() {
    // ==========================
    // TESTING BST TASKS (1-4)
    // ==========================
    cout << "~~~ BST TASKS ~~~" << endl;
    BST tree;
    
    // Task 1: Construct from Array
    int arr[] = {50, 30, 20, 40, 70, 60, 80};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    cout << "Building BST from array: {50, 30, 20, 40, 70, 60, 80}" << endl;
    tree.buildFromArray(arr, n);
    
    cout << "Inorder Traversal: ";
    tree.inorder();

    // Task 2: Search
    tree.search(40);
    tree.search(99);

    // Task 3: Height
    tree.showHeight();

    // Task 4: Min/Max
    tree.showMinMax();

    cout << endl;

    // ==========================
    // TESTING LINKED LIST TASK (5)
    // ==========================
    cout << "~~~ LINKED LIST TASK ~~~" << endl;
    LinkedList ll;
    
    // Create list: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    cout << "Original List: ";
    ll.printList(head);

    cout << "~~Reversing in k=2 groups" << endl;
    head = ll.reverseKGroup(head, 2);

    cout << "Modified List: ";
    ll.printList(head);

    system("pause>0");
    return 0;
}