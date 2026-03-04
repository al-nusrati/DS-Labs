#include <iostream>
#include <string>
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
    int size; // THE GAME CHANGER: O(1) Time Complexity for size checks

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
        size = 0; // Initialize size
    }

    DoublyLinkedList(const DoublyLinkedList& other) {
        head = nullptr;
        tail = nullptr;
        size = 0;
        node<T>* temp = other.head;
        while(temp != nullptr) {
            insertAtEnd(temp->data);
            temp = temp->next;
        }
    }

    ~DoublyLinkedList() {
        freeMemory();
    }

    // --- O(1) Time Complexity ---
    int nodeCount() {
        return size; 
    }

    bool isEmpty() {
        return (size == 0);
    }

    void insertAtBeginning(T val) {
        node<T>* newNode = getNewNode(val);
        
        if(head == nullptr) { 
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++; // Increment size
    }

    void insertAtEnd(T val) {
        node<T>* newNode = getNewNode(val);
        
        if(head == nullptr) {  
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++; // Increment size
    }

    void insertAtAnyPos(int position, T val) {
        // Now this check is O(1) instead of O(N)
        if(position <= 0 || position > size + 1) {
            return; // Silently return, let main() handle errors
        }
        
        if(position == 1) {
            insertAtBeginning(val);
            return;
        }
        
        if(position == size + 1) {
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
        size++; // Increment size
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
            size--; // Decrement size
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
            size--; // Decrement size
        }
    }

    void deleteAtAnyPos(int position) {
        // O(1) bounds check
        if(isEmpty() || position <= 0 || position > size) {
            return;
        }
        
        if(position == 1) {
            deleteFromStart();
            return;
        }
        
        if(position == size) {
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
        size--; // Decrement size
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

    T getNthNode(int n) {
        if(n < 1 || n > size) {
            return T(); // Return default value if out of bounds
        }
        
        node<T>* temp = head;
        for(int i = 1; i < n; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    T getLastNodeData() {
        if(tail == nullptr) {
            return T();
        }
        return tail->data;
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

    // Reusability Fix: Returns the data instead of printing it
    T findMiddle() {
        if(head == nullptr) {
            return T();
        }
        
        node<T>* slow = head;
        node<T>* fast = head;
        
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow->data;
    }

    void traverseForward() {
        node<T>* temp = head;
        while(temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
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
        size = 0; // Reset size
    }
};

// int main() {
//     DoublyLinkedList<int> list;

//     cout << "--- Inserting Hardcoded Nodes ---" << endl;
//     list.insertAtBeginning(20);
//     list.insertAtBeginning(30);
//     list.insertAtBeginning(40);
//     list.insertAtBeginning(50);
//     list.insertAtBeginning(60);
//     list.insertAtBeginning(70);
//     list.insertAtEnd(80);
//     list.insertAtEnd(90);
    
//     cout << "List Forward: ";
//     list.traverseForward();

//     list.deleteFromEnd();
//     list.deleteFromStart();
    
//     cout << "List Reverse after deletes: ";
//     list.traverseReverse();

//     // Demonstrating the O(1) Time Complexity
//     cout << "\nTotal Nodes (Calculated in O(1) time): " << list.nodeCount() << endl;
    
//     // Demonstrating Reusability
//     cout << "Middle Element: " << list.findMiddle() << endl;

//     cout << "\n--- Interactive Input Test (Using Template) ---" << endl;
//     int userVal = getValidInput<int>("Enter an integer to insert at position 3: ");
//     list.insertAtAnyPos(3, userVal);
    
//     cout << "Updated List: ";
//     list.traverseForward();

//     system("pause>0");
//     return 0;
// }