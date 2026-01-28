#include <iostream>
using namespace std;

struct node {
    int data;
    node *next;
};

class linkedList {
private:
    node *head;

    node* getNewNode(int val){
        node *newNode = new node;
        newNode->data = val;
        newNode->next = NULL;
        return newNode;
    }

    node* getLastNode(){
        if (head == NULL){ return NULL; }
        node *nPtr = head;
        while (nPtr->next != NULL){
            nPtr = nPtr->next;
        }
        return nPtr;
    }

public:
    linkedList() { head = NULL; }
    
    linkedList(const linkedList& list) {
        head = NULL;
        node* temp = list.head;
        while(temp != NULL) {
            insertAtEnd(temp->data);
            temp = temp->next;
        }
    }
    
    ~linkedList() { freeMemory(); }

    void insertAtBeginning(int val) {
        node *nNode = getNewNode(val);
        nNode->next = head;
        head = nNode;
    }

    void insertAtEnd(int pos) {
        node *nNode = getNewNode(pos);
        if(head == NULL){
            head = nNode;
            return ;
        }
        node *lastNode = getLastNode();     
        lastNode->next = nNode;           
    }

    void insertAtAnyPos(int position, int val) {
        if(position < 0 || position > nodeCount()) {
            cout << "Invalid position, cant be inserted!" << endl;
            return;
        }
        if(position == 0) {
            insertAtBeginning(val);
            return;
        }
        node *nNode = getNewNode(val);
        node *temp = head;
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
        node *temp = head;         
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
        node* temp = head;
        while(temp->next->next != NULL){
            temp = temp->next;      
        }
        delete temp->next;         
        temp->next = nullptr; 
    }

    void removeAtAnyPos(node* rmvNode) {
        if(head == NULL || rmvNode == NULL) {
            cout << "List is empty or invalid node!" << endl;
            return;
        }
        if(head == rmvNode) {
            deleteFromStart();
            return;
        }
        node *temp = head;
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
        node *ptr = head;
        int count = 0;
        while (ptr != NULL){
            ++count;
            ptr = ptr->next;
        }
        return count;
    }

    int getLastNodeData() {
        int pos = 0;
        node *ptr = head;
        while (ptr != NULL){
            pos = ptr->data;
            ptr = ptr->next;
        }
        return pos;
    }

    bool isEmpty() { return (head == NULL); }

    bool searchData(int pos) {
        node *temp = head;
        while (temp != NULL){
            if(temp->data == pos){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void traverseForward() {
        node *n1 = head;
        while(n1 != NULL){
            cout << n1->data << " -> ";
            n1 = n1->next;
        }
        cout << "NULL" << endl;
    }

    void freeMemory() {
        node *temp;
        while (head != NULL){
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};


int main (){
    linkedList list;

    list.insertAtBeginning(10);
    list.insertAtBeginning(20);
    list.insertAtBeginning(30);

    list.insertAtEnd(40);
    list.insertAtEnd(50);

    list.traverseForward();

    
}