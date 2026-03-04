#include <iostream>
#include <string>

#include "Heap.cpp"
#include "DLL.cpp"
#include "BST.cpp"
#include "Queue.cpp"

using namespace std;

struct Revision {
    int revNumber;
    string content;
    
};

class Document {
public:
    int id;
    string title;
    string author;
    string status; 
    
    
    DynamicStack<Revision> revisions;
    int revCounter;

    Document(int _id, string _t, string _a) {
        id = _id;
        title = _t;
        author = _a;
        status = "pending";
        revCounter = 0;
    }

    bool operator<=(const Document& other) const { return id <= other.id; }
    bool operator>(const Document& other) const { return id > other.id; }
    bool operator<(const Document& other) const { return id < other.id; }
    bool operator==(const Document& other) const { return id == other.id; }

    
    friend ostream& operator<<(ostream& os, const Document& d) {
        os << "ID: " << d.id << " " << d.title << " Author: " << d.author << " Status: " << d.status << endl;
        return os;
    }
};


class System {
private:
    BST<Document> bst_obj;                  
    DynamicQueue<Document*> queue;    

public:
    
    void submission(int id, string title, string author) {
        Document newDoc(id, title, author);
        bst_obj.insert(newDoc);
        
        Document* ptr = new Document(newDoc); 
        queue.enqueue(ptr);
        
        
        cout << "Doc " << id << " submitted and added ready queue\n\n";
    }

    
    void placement() {
        if (queue.isEmpty()) {
            cout << "No docs to review.\n";
            return;
        }
        Document* doc = queue.getFront();
        doc->status = "inreview";
        queue.dequeue();
        cout << "-> Document " << doc->id << " changed to inReview.\n\n";
    }

    void addRevision(Document* doc, string content) {
        doc->revCounter++;
        Revision r = {doc->revCounter, content};
        doc->revisions.push(r);
        cout << "-> Revis added to stack is " << doc->id << endl;
    }

    void undoDoc(Document* doc) {
        if (!doc->revisions.isEmpty()) {
            doc->revisions.pop();
            doc->revCounter-- ;
            cout << "-> Most recent revision popped from stack " << doc->id << "\n\n";
        }
    }

    void finalStatus(Document* doc, string newStatus) {
        string temp = doc->status;
        doc->status = newStatus;

        cout << "-> Doc " << doc->id << " marked with new status " << newStatus << "\n\n";
    }

    
    void display() {
        cout << "~~~~~ Displaying System Files ~~~~~\n\n";
        bst_obj.inorder(); 
    }


};

int main() {
    System sys;
    
    sys.submission(101, "Task 1", "Ali");
    sys.submission(102, "Task 2", "Jawad");
    sys.submission(103, "Task 3", "Amna");

    sys.display();
    sys.placement();

    system("pause>0");
    return 0;
}