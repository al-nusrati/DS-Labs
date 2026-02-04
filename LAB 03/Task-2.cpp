#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node<T>* next;
    node<T>* prev;
};

template <typename T>
class DoublyLinkedList {
private:
    node<T>* head;
    node<T>* tail;

    node<T>* getNewNode(T val) {
        node<T>* newNode = new node<T>;
        newNode->data = val;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }

    node<T>* getLastNode() {
        return tail;
    }

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    DoublyLinkedList(const DoublyLinkedList& other) {
        head = nullptr;
        tail = nullptr;
        node<T>* temp = other.head;
        while(temp != nullptr) {
            insertAtEnd(temp->data);
            temp = temp->next;
        }
    }

    ~DoublyLinkedList() {
        freeMemory();
    }

    void insertAtBeginning(T val) {
        node<T>* newNode = getNewNode(val);
        
        if(head == nullptr) { 
            head = tail = newNode;
            return;
        }
        
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void insertAtEnd(T val) {
        node<T>* newNode = getNewNode(val);
        
        if(head == nullptr) {  
            head = tail = newNode;
            return;
        }
        
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void insertAtAnyPos(int position, T val) {
        if(position <= 0 || position > nodeCount() + 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if(position == 1) {
            insertAtBeginning(val);
            return;
        }
        
        if(position == nodeCount() + 1) {
            insertAtEnd(val);
            return;
        }
        
        node<T>* newNode = getNewNode(val);
        node<T>* temp = head;
        //---------------------------------------------
        for(int i = 1; i < position - 1; i++) {
            temp = temp->next;
        }
        
        newNode->next = temp->next;
        newNode->prev = temp;
        
        if(temp->next != nullptr) {
            temp->next->prev = newNode;
        }
        
        temp->next = newNode;
    }

    void deleteFromStart() {
        if(!isEmpty()){
            node<T>* temp = head;
            if( head == tail) {  
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
            
            delete temp;
        }    
    }

    void deleteFromEnd() {
        if(!isEmpty()) { 
            node<T>* temp = tail;
            
            if(head == tail) { 
                head = tail = nullptr;
            } else {
                tail = tail->prev;
                tail->next = nullptr;
            }
            delete temp;
        }
    }

    void deleteAtAnyPos(int position) {
        if(head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        if(position <= 0 || position > nodeCount()) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if(position == 1) {
            deleteFromStart();
            return;
        }
        
        if(position == nodeCount()) {
            deleteFromEnd();
            return;
        }
        
        node<T>* temp = head;
        for(int i = 1; i < position; i++) {
            temp = temp->next;
        }
        
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        
        delete temp;
    }

    void reverse() {
        if(head == nullptr || head->next == nullptr) {
            return;
        }
        
        node<T>* current = head;
        node<T>* temp = nullptr;
        
        tail = head;
        
        while(current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if(temp != nullptr) {
            head = temp->prev;
        }
    }

    int nodeCount() {
        int count = 0;
        node<T>* temp = head;
        while(temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    T getNthNode(int n) {
        if(n < 1 || n > nodeCount()) {
            cout << "Invalid position!" << endl;
            return T();
        }
        
        node<T>* temp = head;
        for(int i = 1; i < n; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    T getLastNodeData() {
        if(tail == nullptr) {
            cout << "List is empty!" << endl;
            return T();
        }
        return tail->data;
    }

    bool isEmpty() {
        return (head == nullptr);
    }

    bool searchData(T val) {
        node<T>* temp = head;
        while(temp != nullptr) {
            if(temp->data == val) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void findMiddle() {
        if(head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        node<T>* slow = head;
        node<T>* fast = head;
        
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        cout << "Middle element: " << slow->data << endl;
    }

    void traverseForward() {
        node<T>* temp = head;
        while(temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL " << endl;
    }

    void traverseReverse() {
        node<T>* temp = tail;
        while(temp != nullptr) { 
            cout << temp->data << " -> ";
            temp = temp->prev;
        }
        cout << "NULL" << endl;
    }

    void freeMemory() {
        node<T>* temp;
        while(head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    
    node<T>* getHead() {
        return head;
    }

    node<T>* getTail() {
        return tail;
    }
};

class webBrower {
private:
    DoublyLinkedList<string> historyDLL;
    node<string>* currentPgPtr;

public:
    webBrower() {
        currentPgPtr = nullptr;
    }

    webBrower(string url) {
        historyDLL.insertAtEnd(url);
        currentPgPtr = historyDLL.getHead();
    }

    webBrower(const webBrower& other) {
        historyDLL = other.historyDLL;
        currentPgPtr = historyDLL.getHead();
    }

    ~webBrower() {
        historyDLL.freeMemory();
    }

    //----------------------------------------------

    void visitPage(string url) {
    historyDLL.insertAtEnd(url);
    currentPgPtr = historyDLL.getTail();   // this will get the tail
    cout << "Visited: " << url << endl;
    }

    string back() {
        if(currentPgPtr == nullptr || currentPgPtr->prev == nullptr) {      // to check if current webpage node is null or first node.
            string temp = "Can't go back -  at the beginning of history of webswer.";
            return temp;
        }
        currentPgPtr = currentPgPtr->prev;  // copy previous webpage into current page
        cout << "Back to: " << currentPgPtr->data << endl;
        return currentPgPtr->data;
    }

    string forward() {
        if(currentPgPtr == nullptr || currentPgPtr->next == nullptr) {  // to check if current webpage pointer is null or last node.
            string temp = "Can't go forward - at the end of webrowser history.";
            return temp;
        }
        currentPgPtr = currentPgPtr->next;  // copy next webpage into current page
        cout << "Forward to: " << currentPgPtr->data << endl;
        return currentPgPtr->data;
    }

    void displayHistory() {
        cout << "~~~~webBrower history~~~~: ";
        historyDLL.traverseForward();
        }
};

int main() {
    webBrower browser("stack.com");
    browser.displayHistory();
    browser.visitPage("google.com");
    browser.visitPage("facebook.com");
    browser.back();
    browser.displayHistory();
    browser.forward();
    browser.visitPage("youtube.com");
    browser.displayHistory();

    return 0;
}