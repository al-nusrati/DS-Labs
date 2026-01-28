#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node<T> *next;
};

template <typename T>
class linkedList {
private:
    node<T> *head;

    node<T>* getNewNode(int pos){
        node<T> *newNode = new node<T>;
        newNode->data = pos;
        newNode->next = NULL;
        return newNode;
    }

    node<T>* getLastNode(){
        if (head == NULL){ return NULL; }
        node<T> *nPtr = head;
        while (nPtr->next != NULL){
            nPtr = nPtr->next;
        }
        return nPtr;
    }

public:
    linkedList() { head = NULL; }
    
    linkedList(const linkedList& other) {
        head = NULL;
        node<T>* temp = other.head;
        while(temp != NULL) {
            insertAtEnd(temp->data);
            temp = temp->next;
        }
    }
    
    ~linkedList() { freeMemory(); }

    void insertAtBeginning(int pos) {
        node<T> *nNode = getNewNode(pos);
        nNode->next = head;
        head = nNode;
    }

    void insertAtEnd(int pos) {
        node<T> *nNode = getNewNode(pos);
        if(head == NULL){
            head = nNode;
            return ;
        }
        node<T> *lastNode = getLastNode();     
        lastNode->next = nNode;           
    }

    void insertAtAnyPos(int position, int val) {
        if(position < 0 || position > nodeCount()) {
            cout << "Invalid position!" << endl;
            return;
        }
        if(position == 0) {
            insertAtBeginning(val);
            return;
        }
        node<T> *nNode = getNewNode(val);
        node<T> *temp = head;
        for(int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        nNode->next = temp->next;
        temp->next = nNode;
    }

    void deleteFromStart() {
        if(head == NULL){
            cout << "List is empty, cannot delete it!" << endl;
            return;     
        }
        node<T> *temp = head;         
        head = head->next;          
        delete temp; 
    }

    void deleteFromEnd() {
        if(head == NULL){
            cout << "List is empty, cannot delete it!" << endl;
            return;
        }
        if(head->next == NULL){
            delete head;
            head = nullptr;
            return;
        }
        node<T>* temp = head;
        while(temp->next->next != NULL){
            temp = temp->next;      
        }
        delete temp->next;         
        temp->next = nullptr; 
    }

    void removeAtAnyPos(node<T>* rmvNode) {
        if(head == NULL || rmvNode == NULL) {
            cout << "List is empty or invalid node<T>!" << endl;
            return;
        }
        if(head == rmvNode) {
            deleteFromStart();
            return;
        }
        node<T> *temp = head;
        while(temp != NULL && temp->next != rmvNode) {
            temp = temp->next;
        }
        if(temp == NULL) {
            cout << "Node not found in the list!" << endl;
            return;
        }
        temp->next = rmvNode->next;
        delete rmvNode;
    }

    int nodeCount() {
        node<T> *ptr = head;
        int count = 0;
        while (ptr != NULL){
            ++count;
            ptr = ptr->next;
        }
        return count;
    }

    int getLastNodeData() {
        int pos = 0;
        node<T> *ptr = head;
        while (ptr != NULL){
            pos = ptr->data;
            ptr = ptr->next;
        }
        return pos;
    }

    bool isEmpty() { return (head == NULL); }

    bool searchData(int pos) {
        node<T> *temp = head;
        while (temp != NULL){
            if(temp->data == pos){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void traverseForward() {
        node<T> *n1 = head;
        while(n1 != NULL){
            cout << n1->data << " -> ";
            n1 = n1->next;
        }
        cout << "NULL" << endl;
    }

    void freeMemory() {
        node<T> *temp;
        while (head != NULL){
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};


int main (){

    // 1st task
    linkedList<int> list;

    // 2nd task
    linkedList<int> copyList(list);

    // 3rd task
    cout << "Is list empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    // 4th task
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    list.insertAtEnd(5);
    cout << "Inserted values 1-5 at the end." << endl;

    // 5th task
    cout << "Is list empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    // 6th task
    list.traverseForward();

    // 7th task
    list.deleteFromStart();
    cout << "Deleted first element." << endl;

    // 8th task
    list.traverseForward();

    // 9th task
    list.insertAtBeginning(6);
    cout << "6 inserted at start." << endl;

    // 10th task
    list.traverseForward();

    // 11th task
    list.insertAtEnd(9);
    cout << "9 inserted at end." << endl;

    // 12th task
    list.traverseForward();

    // 13th task
    list.deleteFromEnd();
    cout << "Deleted last element." << endl;

    // 14th task
    list.traverseForward();

    // 15th task
    //
    list.removeAtAnyPos();

    return 0;
}