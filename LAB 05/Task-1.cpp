//binary tree
#include <iostream>
using namespace std;

struct node {
    int data;
    //----------
    node *left;
    node *right;
};

void isEmpty(node *root){
    if(root == nullptr){
        cout << "Tree is empty" << endl;
    }
    else{
        cout << "Tree is not empty" << endl;
    }
};

// --- Create a new node ---
node* createNode(int val) {
    node* newNode = new node;
    newNode->data = val;
    //---
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}


node *bst_insert(node *btNode, int val){
    //--- btNode == nullptr -------------------- (end position)
    if(btNode == nullptr)
    {
        node *newNode = createNode(val);
        btNode = newNode;
        return btNode;
    }

    //--- btNode != nullptr -------------------- (not end position)
    else
    { 
                //  LEFT CHECK
                if (val <= btNode->data)    
                {
                    btNode->left = bst_insert(btNode->left, val);
                }
                //  RIGHT CHECK
                if (val > btNode->data)
                {
                    btNode->right = bst_insert(btNode->right, val);
                }

        return btNode;
    }
}


// --- Find minimum node ---
node* findMin(node *root){
    node *current = root;
    while(current->left != nullptr){
        current = current->left;
    }
    return current;
}


// --- Delete a node ---
node* bst_delete(node *root, int val){
    //--- base case ----------------------------
    if(root == nullptr){
        cout << "Node not found" << endl;
        return nullptr;
    }

    //--- search phase -------------------------
    if(val < root->data)
    {
        root->left = bst_delete(root->left, val);
    }
    else if(val > root->data)
    {
        root->right = bst_delete(root->right, val);
    }

    //--- found the node -----------------------
    else
    {
                // delete leaf
                if(root->left == nullptr && root->right == nullptr)
                {
                    delete root;
                    return nullptr;
                }
                //------------------------------------------------------------------

                // delete internal child
                else if(root->left == nullptr)
                {
                    node *temp = root->right;
                    delete root;
                    return temp;
                }
                else if(root->right == nullptr)
                {
                    node *temp = root->left;
                    delete root;
                    return temp;
                }
                //-----------------------------------------------------------------

                // delete parent
                //  -> inorder (successor) replacement - leftmost node in right subtree
                else
                {
                    node *successor = findMin(root->right);
                    root->data    = successor->data;                          // copy successor value
                    root->right   = bst_delete(root->right, successor->data); // delete successor
                }
    }

    return root;
}


// ============================================================


// --- Inorder   :  Left -> Root -> Right ---
void inorder(node *root){
    if(root){
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// --- Preorder  :  Root -> Left -> Right ---
void preorder(node *root){
    if(root){
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// --- Postorder :  Left -> Right -> Root ---
void postorder(node *root){
    if(root){
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}


// --- Deep copy a tree - preorder ---
node* copyTree(node *root){
    //--- base case ---
    if(root == nullptr) return nullptr;

    //--- copy current node ---
    node *newNode   = createNode(root->data);
    newNode->left   = copyTree(root->left);
    newNode->right  = copyTree(root->right);

    return newNode;
}

// --- Free entire tree ---
void freeTree(node *root){
    if(root){
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}


void findNode(node *root, int val){
    if(root == nullptr){
        cout << "Root is null" << endl;
        return;
    }
    node *current = root;
    while(current != nullptr){
        if(current->data == val){
            cout << "Node found: " << current->data << endl;
            return;
        }
        if(val < current->data){
            cout << "Going left from node: " << current->data << endl;
            current = current->left;
        }
        else{
            cout << "Going right from node: " << current->data << endl;
            current = current->right;
        }
    }

    cout << "Node not found" << endl;
}


// bst = binary search tree
int main() {

    node* root = nullptr;

    root = bst_insert(root, 21);
    root = bst_insert(root, 22);
    root = bst_insert(root, 10);
    root = bst_insert(root, 19);
    root = bst_insert(root, 17);

    cout << "Inorder   : "; inorder(root);   cout << endl;
    cout << "Preorder  : "; preorder(root);  cout << endl;
    cout << "Postorder : "; postorder(root); cout << endl;

    cout << "\nSearching 6: "; findNode(root, 6);
    cout << "\nSearching 21: "; findNode(root, 21);

    root = bst_insert(root, 22);

    bst_delete(root, 78);
    bst_delete(root, 10);

    cout << "Inorder   : "; inorder(root);   cout << endl;

    isEmpty(root);

    cout << "\nCopying tree into root2:\n";
    node* root2 = copyTree(root);
    isEmpty(root2);
    bst_delete(root2, 17);

    cout << "Inorder root : "; inorder(root);   cout << endl;
    cout << "Inorder root2  : "; inorder(root2);   cout << endl;

    bst_delete(root, 19);
    bst_delete(root, 21);
    bst_delete(root, 22);

    cout << "Inorder root2  : "; inorder(root2);   cout << endl;
    cout << "Inorder root : "; inorder(root);   cout << endl;

    cout << "Preorder  : "; preorder(root);  cout << endl;
    cout << "Postorder : "; postorder(root); cout << endl;

    freeTree(root);  root  = nullptr;
    freeTree(root2); root2 = nullptr;

    system("pause>0");
    return 0;
}