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

    // Helper function to find node by station name
    node<T>* findNodeByData(T val) {
        node<T>* temp = head;
        while(temp != nullptr) {
            if(temp->data == val) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Helper function to delete a specific node
    void deleteSpecificNode(node<T>* targetNode) {
        if(targetNode == nullptr) {
            return;
        }
        
        // If it's the only node
        if(head == tail) {
            head = tail = nullptr;
        }
        // If it's the head
        else if(targetNode == head) {
            head = head->next;
            head->prev = nullptr;
        }
        // If it's the tail
        else if(targetNode == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        // If it's in the middle
        else {
            targetNode->prev->next = targetNode->next;
            targetNode->next->prev = targetNode->prev;
        }
        
        delete targetNode;
    }
};

class metroRoute {
private:
    DoublyLinkedList<string> stationDLL;
    node<string>* currentStationPtr;

public:
    metroRoute() {
        currentStationPtr = nullptr;
    }

    metroRoute(string stName) {
        stationDLL.insertAtEnd(stName);
        currentStationPtr = stationDLL.getHead();
    }

    metroRoute(const metroRoute& other) {
        stationDLL = other.stationDLL;
        currentStationPtr = stationDLL.getHead();
    }

    ~metroRoute() {
        stationDLL.freeMemory();
    }

    //----------------------------------------------

    void addStation(string stName, int pos) {
        if(pos <= 0 || pos > stationDLL.nodeCount() + 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        stationDLL.insertAtAnyPos(pos, stName);
        
        // If this is the first station, set current pointer
        if(currentStationPtr == nullptr) {
            currentStationPtr = stationDLL.getHead();
        }
        
        cout << "Station added: " << stName << " at position " << pos << endl;
    }

    void removeStation(string stName) {
        if(stationDLL.isEmpty()) {
            cout << "Route is empty!" << endl;
            return;
        }
        
        node<string>* stationToRemove = stationDLL.findNodeByData(stName);
        
        if(stationToRemove == nullptr) {
            cout << "Station '" << stName << "' not found in route!" << endl;
            return;
        }
        
        // If we're removing the current station, move to previous or next
        if(currentStationPtr == stationToRemove) {
            if(currentStationPtr->prev != nullptr) {
                currentStationPtr = currentStationPtr->prev;
            } else if(currentStationPtr->next != nullptr) {
                currentStationPtr = currentStationPtr->next;
            } else {
                currentStationPtr = nullptr;  // List will be empty
            }
        }
        
        stationDLL.deleteSpecificNode(stationToRemove);
        cout << "Station '" << stName << "' removed from route." << endl;
    }

    void moveForward() {
        if(currentStationPtr == nullptr) {
            cout << "No current station!" << endl;
            return;
        }
        
        if(currentStationPtr->next == nullptr) {
            cout << "Can't move forward - at the end station of route." << endl;
            return;
        }
        
        currentStationPtr = currentStationPtr->next;
        cout << "Moved forward to: " << currentStationPtr->data << endl;
    }

    void moveBackward() {
        if(currentStationPtr == nullptr) {
            cout << "No current station!" << endl;
            return;
        }
        
        if(currentStationPtr->prev == nullptr) {
            cout << "Can't move backward - at the beginning station of route." << endl;
            return;
        }
        
        currentStationPtr = currentStationPtr->prev;
        cout << "Moved backward to: " << currentStationPtr->data << endl;
    }

    void displayRoute() {
        if(stationDLL.isEmpty()) {
            cout << "Route is empty!" << endl;
            return;
        }
        cout << "~~~~ Metro Route ~~~~: ";
        stationDLL.traverseForward();
    }

    void currentStation() {
        if(currentStationPtr == nullptr) {
            cout << "No current station!" << endl;
            return;
        }
        cout << "Current Station: " << currentStationPtr->data << endl;
    }
};

int main() {
    cout << "=== Testing Metro Route System ===" << endl << endl;
    
    // Test 1: Initialize with a station
    cout << "--- Test 1: Initialize Route ---" << endl;
    metroRoute metro("Lahore Junction");
    metro.displayRoute();
    metro.currentStation();
    cout << endl;
    
    // Test 2: Add stations at different positions
    cout << "--- Test 2: Add Stations ---" << endl;
    metro.addStation("Islamabad Metro", 2);
    metro.addStation("Rawalpindi Central", 3);
    metro.addStation("Karachi Terminal", 4);
    metro.displayRoute();
    metro.currentStation();
    cout << endl;
    
    // Test 3: Move forward and backward
    cout << "--- Test 3: Navigate Route ---" << endl;
    metro.moveForward();
    metro.moveForward();
    metro.currentStation();
    metro.displayRoute();
    cout << endl;
    
    metro.moveBackward();
    metro.currentStation();
    cout << endl;
    
    // Test 4: Remove a station
    cout << "--- Test 4: Remove Station ---" << endl;
    metro.removeStation("Rawalpindi Central");
    metro.displayRoute();
    metro.currentStation();
    cout << endl;
    
    // Test 5: Add station in the middle
    cout << "--- Test 5: Add Station in Middle ---" << endl;
    metro.addStation("Multan Express", 2);
    metro.displayRoute();
    cout << endl;
    
    // Test 6: Remove current station
    cout << "--- Test 6: Remove Current Station ---" << endl;
    metro.currentStation();
    metro.removeStation("Islamabad Metro");
    metro.displayRoute();
    metro.currentStation();
    cout << endl;
    
    // Test 7: Navigate to boundaries
    cout << "--- Test 7: Test Boundaries ---" << endl;
    metro.moveBackward();
    metro.moveBackward();  // Should show error
    metro.currentStation();
    cout << endl;
    
    metro.moveForward();
    metro.moveForward();
    metro.moveForward();  // Should show error
    metro.currentStation();
    cout << endl;
    
    // Test 8: Try to remove non-existent station
    cout << "--- Test 8: Remove Non-existent Station ---" << endl;
    metro.removeStation("Peshawar Station");
    cout << endl;
    
    // Test 9: Add at invalid position
    cout << "--- Test 9: Invalid Position ---" << endl;
    metro.addStation("Faisalabad Junction", 10);
    metro.addStation("Quetta Terminal", 0);
    cout << endl;

    return 0;
}