#include <iostream>
#include <string>
using namespace std;

struct Book {
    int    bookID;
    string title;
    string author;
    int    popularity;
};

template <typename T>
struct node {
    T     data;
    //----------
    node *left;
    node *right;
};


template <typename T>
class BST {

private:
    node<T> *root;

    // ---- create node ----
    node<T>* createNode(T val){
        node<T>* newNode = new node<T>;
        newNode->data  = val;
        //---
        newNode->left  = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // ---- find minimum node (used in deletion) ----
    node<T>* findMin(node<T> *cur){
        node<T> *current = cur;
        while(current->left != nullptr){
            current = current->left;
        }
        return current;
    }

    // ---------------------------------------------------

    node<T>* bst_insert(node<T> *btNode, T val){
        //--- btNode == nullptr -------------------- (end position)
        if(btNode == nullptr)
        {
            node<T> *newNode = createNode(val);
            btNode = newNode;
            return btNode;
        }

        //--- btNode != nullptr -------------------- (not end position)
        else
        {
                    //  LEFT CHECK
                    if(val.popularity <= btNode->data.popularity)
                    {
                        btNode->left  = bst_insert(btNode->left,  val);
                    }
                    //  RIGHT CHECK
                    if(val.popularity  > btNode->data.popularity)
                    {
                        btNode->right = bst_insert(btNode->right, val);
                    }

            return btNode;
        }
    }

    // ---------------------------------------------------

    node<T>* bst_delete(node<T> *cur, int pop){
        //--- base case ----------------------------
        if(cur == nullptr){
            cout << "Node not found" << endl;
            return nullptr;
        }

        //--- search phase -------------------------
        if(pop < cur->data.popularity)
        {
            cur->left  = bst_delete(cur->left,  pop);
        }
        else if(pop > cur->data.popularity)
        {
            cur->right = bst_delete(cur->right, pop);
        }

        //--- found the node -----------------------
        else
        {
                    // delete leaf
                    if(cur->left == nullptr && cur->right == nullptr)
                    {
                        delete cur;
                        return nullptr;
                    }
                    //------------------------------------------------------------------

                    // delete internal child
                    else if(cur->left == nullptr)
                    {
                        node<T> *temp = cur->right;
                        delete cur;
                        return temp;
                    }
                    else if(cur->right == nullptr)
                    {
                        node<T> *temp = cur->left;
                        delete cur;
                        return temp;
                    }
                    //-----------------------------------------------------------------

                    // delete parent
                    //  -> inorder (successor) replacement - leftmost node in right subtree
                    else
                    {
                        node<T> *successor = findMin(cur->right);
                        cur->data          = successor->data;                                       // copy successor value
                        cur->right         = bst_delete(cur->right, successor->data.popularity);   // delete successor
                    }
        }

        return cur;
    }

    // ---------------------------------------------------

    void findBook(node<T> *cur, int pop){
        if(cur == nullptr){
            cout << "Root is null" << endl;
            return;
        }
        node<T> *current = cur;
        while(current != nullptr){
            if(current->data.popularity == pop){
                cout << "Book found: [ID: " << current->data.bookID << "] \"" << current->data.title << "\" by "  
                << current->data.author << "  |  Popularity: " << current->data.popularity << "\n";
                return;
            }
            if(pop < current->data.popularity){
                cout << "Going left from: \"" << current->data.title << "\"\n";
                current = current->left;
            }
            else{
                cout << "Going right from: \"" << current->data.title << "\"\n";
                current = current->right;
            }
        }
        cout << "Book not found" << endl;
    }

    // ============================================================
    //  TRAVERSALS
    // ============================================================

    // --- Inorder   :  Left -> Root -> Right  (sorted by popularity) ---
    void inorder(node<T> *cur){
        if(cur){
            inorder(cur->left);
            cout << "  [ID: " << cur->data.bookID << "] \"" << cur->data.title << "\" by " << cur->data.author << "  |  Popularity: " 
            << cur->data.popularity << "\n";
            inorder(cur->right);
        }
    }

    // --- Preorder  :  Root -> Left -> Right ---
    void preorder(node<T> *cur){
        if(cur){
            cout << "  [ID: " << cur->data.bookID << "] \""    << cur->data.title << "\" by "  << cur->data.author 
            << "  |  Popularity: " << cur->data.popularity << "\n";
            preorder(cur->left);
            preorder(cur->right);
        }
    }

    // --- Postorder :  Left -> Right -> Root ---
    void postorder(node<T> *cur){
        if(cur){
            postorder(cur->left);
            postorder(cur->right);
            cout << "  [ID: " << cur->data.bookID << "] \""    << cur->data.title << "\" by "  
            << cur->data.author << "  |  Popularity: " << cur->data.popularity << "\n";
        }
    }

    // ---------------------------------------------------

    // --- count all nodes ---
    int countNodes(node<T> *cur){
        if(cur == nullptr) return 0;
        return 1 + countNodes(cur->left) + countNodes(cur->right);
    }

    // --- top-K books (reverse inorder - highest popularity first) ---
    void topK(node<T> *cur, int k, int &count){
        if(cur == nullptr || count >= k) return;

        topK(cur->right, k, count);         // go right first - highest popularity

        if(count < k){
            cout << "  #" << count+1 << " [ID: " << cur->data.bookID << "] \""   << cur->data.title 
            << "\" by " << cur->data.author << "  |  Popularity: " << cur->data.popularity << "\n";
            count++;
        }

        topK(cur->left, k, count);
    }

    // --- range query ---
    void rangeQuery(node<T> *cur, int minScore, int maxScore){
        if(cur == nullptr) return;

        if(cur->data.popularity > minScore)     // explore left only if possible
            rangeQuery(cur->left, minScore, maxScore);

        if(cur->data.popularity >= minScore && cur->data.popularity <= maxScore){
            cout << "  [ID: " << cur->data.bookID << "] \""    << cur->data.title
            << "\" by "  << cur->data.author << "  |  Popularity: " << cur->data.popularity << "\n";
        }

        if(cur->data.popularity < maxScore)     // explore right only if possible
            rangeQuery(cur->right, minScore, maxScore);
    }


    // --- deep copy a tree - preorder ---
    node<T>* copyTree(node<T> *cur){
        //--- base case ---
        if(cur == nullptr) return nullptr;

        //--- copy current node ---
        node<T> *newNode  = createNode(cur->data);
        newNode->left     = copyTree(cur->left);
        newNode->right    = copyTree(cur->right);

        return newNode;
    }

    // --- free entire tree ---
    void freeTree(node<T> *cur){
        if(cur){
            freeTree(cur->left);
            freeTree(cur->right);
            delete cur;
        }
    }

// ============================================================
public:
// ============================================================

    // --- constructor / copy constructor / destructor ---
    BST()                 : root(nullptr) {}
    BST(const BST &other) : root(copyTree(other.root)) {}
    ~BST()                { freeTree(root); root = nullptr; }

    // ---------------------------------------------------

    void isEmpty(){
        if(root == nullptr)
            cout << "Tree is empty" << endl;
        else
            cout << "Tree is not empty" << endl;
    }

    void Insert(T val){
        root = bst_insert(root, val);
    }

    void Delete(int pop){
        root = bst_delete(root, pop);
    }

    void Search(int pop){
        findBook(root, pop);
    }

    void Inorder()   { cout << "Inorder   :\n"; inorder(root);   cout << endl; }
    void Preorder()  { cout << "Preorder  :\n"; preorder(root);  cout << endl; }
    void Postorder() { cout << "Postorder :\n"; postorder(root); cout << endl; }

    void CountNodes(){
        cout << "Total books: " << countNodes(root) << "\n";
    }

    void TopKBooks(int k){
        cout << "--- Top " << k << " Books ---\n";
        int count = 0;
        topK(root, k, count);
    }

    void RangeQuery(int minScore, int maxScore){
        cout << "--- Books with popularity [" << minScore << " - " << maxScore << "] ---\n";
        rangeQuery(root, minScore, maxScore);
    }
};


// ============================================================
//  MAIN
// ============================================================
int main(){

    BST<Book> catalog;

    catalog.Insert({101, "The Pragmatic Programmer",   "Hunt & Thomas",  95});
    catalog.Insert({102, "Clean Code",                 "Robert Martin",  88});
    catalog.Insert({103, "CLRS Algorithms",            "Cormen et al.",  76});
    catalog.Insert({104, "Design Patterns",            "Gang of Four",   82});
    catalog.Insert({105, "The Mythical Man-Month",     "Brooks",         60});
    catalog.Insert({106, "Code Complete",              "McConnell",      73});
    catalog.Insert({107, "Structure & Interpretation", "Abelson",        91});

    // ---- Traversals ----
    catalog.Inorder();
    catalog.Preorder();
    catalog.Postorder();

    // ---- Count ----
    catalog.CountNodes();

    // ---- Search ----
    cout << "\nSearching for popularity = 82:\n"; catalog.Search(82);
    cout << "\nSearching for popularity = 55 (not in catalog):\n"; catalog.Search(55);

    // ---- Top-K ----
    cout << "\n"; catalog.TopKBooks(3);

    // ---- Range Query ----
    cout << "\n"; catalog.RangeQuery(75, 92);

    // ---- Deletion ----
    cout << "\nDeleting popularity 88 (Clean Code):\n";
    catalog.Delete(88);
    catalog.Inorder();

    catalog.isEmpty();

    // ---- Copy constructor ----
    cout << "\nCopying catalog into catalog2:\n";
    BST<Book> catalog2(catalog);
    catalog2.isEmpty();

    catalog2.Delete(76);

    cout << "Inorder catalog  :\n"; catalog.Inorder();
    cout << "Inorder catalog2 :\n"; catalog2.Inorder();

    system("pause>0");
    return 0;
}