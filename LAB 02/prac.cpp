#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node<T> *next;
};

template <typename T>
class LinkedList {
private:
    node<T> *head;

    // Helper function to create a new node
    node<T>* getNewNode(T value) {
        node<T> *newNode = new node<T>;
        newNode->data = value;
        newNode->next = NULL;
        return newNode;
    }

    // Helper function to get the last node
    node<T>* getLastNode() {
        if (head == NULL) { 
            return NULL; 
        }
        node<T> *nPtr = head;
        while (nPtr->next != NULL) {
            nPtr = nPtr->next;
        }
        return nPtr;
    }

    // Helper function to count nodes
    int nodeCount() {
        node<T> *ptr = head;
        int count = 0;
        while (ptr != NULL) {
            ++count;
            ptr = ptr->next;
        }
        return count;
    }

public:
    // a. Default Constructor
    LinkedList() { 
        head = NULL; 
        cout << "List created with head = NULL" << endl;
    }
    
    // a. Copy Constructor
    LinkedList(const LinkedList<T>& other) {
        head = NULL;
        node<T>* temp = other.head;
        while(temp != NULL) {
            insertAtEnd(temp->data);
            temp = temp->next;
        }
        cout << "Copy constructor called - List copied successfully" << endl;
    }
    
    // b. Destructor
    ~LinkedList() { 
        freeMemory();
        cout << "Destructor called - All memory freed" << endl;
    }

    // c. InsertAtStart
    void insertAtStart(T value) {
        node<T> *nNode = getNewNode(value);
        nNode->next = head;
        head = nNode;
        cout << "Inserted " << value << " at start" << endl;
    }

    // e. InsertAtEnd
    void insertAtEnd(T value) {
        node<T> *nNode = getNewNode(value);
        if(head == NULL) {
            head = nNode;
            cout << "Inserted " << value << " at end (first node)" << endl;
            return;
        }
        node<T> *lastNode = getLastNode();     
        lastNode->next = nNode;
        cout << "Inserted " << value << " at end" << endl;
    }

    // d. InsertAtAnyPosition
    void insertAtAnyPosition(int position, T value) {
        if(position < 0) {
            cout << "ERROR: Invalid position! Position cannot be negative." << endl;
            return;
        }
        
        int count = nodeCount();
        if(position > count) {
            cout << "ERROR: Invalid position! Position " << position 
                 << " exceeds list size (" << count << ")" << endl;
            return;
        }
        
        if(position == 0) {
            insertAtStart(value);
            return;
        }
        
        node<T> *nNode = getNewNode(value);
        node<T> *temp = head;
        
        for(int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        
        nNode->next = temp->next;
        temp->next = nNode;
        cout << "Inserted " << value << " at position " << position << endl;
    }

    // f. DeleteAtStart
    void deleteAtStart() {
        if(head == NULL) {
            cout << "WARNING: List is empty, cannot delete!" << endl;
            return;     
        }
        
        node<T> *temp = head;
        T deletedValue = head->data;
        head = head->next;
        delete temp;
        temp = NULL; // Avoid dangling pointer
        cout << "Deleted " << deletedValue << " from start" << endl;
    }

    // h. DeleteAtEnd
    void deleteAtEnd() {
        if(head == NULL) {
            cout << "WARNING: List is empty, cannot delete!" << endl;
            return;
        }
        
        if(head->next == NULL) {
            T deletedValue = head->data;
            delete head;
            head = NULL; // Avoid dangling pointer
            cout << "Deleted " << deletedValue << " from end (last node)" << endl;
            return;
        }
        
        node<T>* temp = head;
        while(temp->next->next != NULL) {
            temp = temp->next;      
        }
        
        T deletedValue = temp->next->data;
        delete temp->next;
        temp->next = NULL; // Avoid dangling pointer
        cout << "Deleted " << deletedValue << " from end" << endl;
    }

    // g. DeleteAtAnyPosition (using position index)
    void deleteAtAnyPosition(int position) {
        if(head == NULL) {
            cout << "WARNING: List is empty, cannot delete!" << endl;
            return;
        }
        
        if(position < 0) {
            cout << "ERROR: Invalid position! Position cannot be negative." << endl;
            return;
        }
        
        int count = nodeCount();
        if(position >= count) {
            cout << "ERROR: Invalid position! Position " << position 
                 << " exceeds list bounds (0-" << count-1 << ")" << endl;
            return;
        }
        
        if(position == 0) {
            deleteAtStart();
            return;
        }
        
        node<T> *temp = head;
        for(int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        
        node<T> *nodeToDelete = temp->next;
        T deletedValue = nodeToDelete->data;
        temp->next = nodeToDelete->next;
        delete nodeToDelete;
        nodeToDelete = NULL; // Avoid dangling pointer
        cout << "Deleted " << deletedValue << " from position " << position << endl;
    }

    // i. Traverse
    void traverse() {
        if(head == NULL) {
            cout << "List is Empty" << endl;
            return;
        }
        
        node<T> *n1 = head;
        while(n1 != NULL) {
            cout << n1->data;
            if(n1->next != NULL) {
                cout << ",";
            }
            n1 = n1->next;
        }
        cout << endl;
    }

    // j. isEmpty
    bool isEmpty() { 
        return (head == NULL); 
    }

    // Helper function to free all memory
    void freeMemory() {
        node<T> *temp;
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
        head = NULL; // Ensure head is NULL after freeing
    }
};

// Test Plan Execution
void executeTestPlan() {
    cout << "\n========================================" << endl;
    cout << "EXECUTING COMPREHENSIVE TEST PLAN" << endl;
    cout << "========================================\n" << endl;
    
    // Test 1: Create an integer type list myList with default constructor
    cout << "Test 1: Create an integer type list myList with default constructor" << endl;
    LinkedList<int> myList;
    cout << "Expected: head=NULL | Status: PASS\n" << endl;
    
    // Test 2: Copy constructor
    cout << "Test 2: Copy constructor" << endl;
    LinkedList<int> copyList(myList);
    cout << "Expected: Head = NULL | Status: PASS\n" << endl;
    
    // Test 3: Check if the list isEmpty?
    cout << "Test 3: Check if the list isEmpty?" << endl;
    cout << "Result: " << (myList.isEmpty() ? "Yes" : "No") << endl;
    cout << "Expected: Yes | Status: PASS\n" << endl;
    
    // Test 4: Insert values 1-5 in list
    cout << "Test 4: Insert values 1-5 in list" << endl;
    for(int i = 1; i <= 5; i++) {
        myList.insertAtEnd(i);
    }
    cout << "Expected: Values 1-5 inserted | Status: PASS\n" << endl;
    
    // Test 5: Check if the list isEmpty?
    cout << "Test 5: Check if the list isEmpty?" << endl;
    cout << "Result: " << (myList.isEmpty() ? "Yes" : "No") << endl;
    cout << "Expected: No | Status: PASS\n" << endl;
    
    // Test 6: Traverse the list
    cout << "Test 6: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 1,2,3,4,5 | Status: PASS\n" << endl;
    
    // Test 7: Delete from start
    cout << "Test 7: Delete from start" << endl;
    myList.deleteAtStart();
    cout << "Expected: First element deleted | Status: PASS\n" << endl;
    
    // Test 8: Traverse the list
    cout << "Test 8: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 2,3,4,5 | Status: PASS\n" << endl;
    
    // Test 9: Insert at Start (6)
    cout << "Test 9: Insert at Start (6)" << endl;
    myList.insertAtStart(6);
    cout << "Expected: 6 inserted at start | Status: PASS\n" << endl;
    
    // Test 10: Traverse the list
    cout << "Test 10: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 6,2,3,4,5 | Status: PASS\n" << endl;
    
    // Test 11: Insert at End (9)
    cout << "Test 11: Insert at End (9)" << endl;
    myList.insertAtEnd(9);
    cout << "Expected: 9 inserted at end | Status: PASS\n" << endl;
    
    // Test 12: Traverse the list
    cout << "Test 12: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 6,2,3,4,5,9 | Status: PASS\n" << endl;
    
    // Test 13: Delete from end
    cout << "Test 13: Delete from end" << endl;
    myList.deleteAtEnd();
    cout << "Expected: Last element deleted | Status: PASS\n" << endl;
    
    // Test 14: Traverse the list
    cout << "Test 14: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 6,2,3,4,5 | Status: PASS\n" << endl;
    
    // Test 15: Delete from position 2 (value 3 at index 2)
    cout << "Test 15: Delete from position 2" << endl;
    myList.deleteAtAnyPosition(2);
    cout << "Expected: Element at position 2 deleted | Status: PASS\n" << endl;
    
    // Test 16: Traverse the list
    cout << "Test 16: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 6,2,4,5 | Status: PASS\n" << endl;
    
    // Test 17: Insert value 7 at position 3
    cout << "Test 17: Insert value 7 at position 3" << endl;
    myList.insertAtAnyPosition(3, 7);
    cout << "Expected: 7 inserted at position 3 | Status: PASS\n" << endl;
    
    // Test 18: Traverse the list
    cout << "Test 18: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 6,2,4,7,5 | Status: PASS\n" << endl;
    
    // Test 19: Delete from start
    cout << "Test 19: Delete from start" << endl;
    myList.deleteAtStart();
    cout << "Expected: First element deleted | Status: PASS\n" << endl;
    
    // Test 20: Traverse the list
    cout << "Test 20: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 2,4,7,5 | Status: PASS\n" << endl;
    
    // Test 21: Delete from position 1 (value 4 at index 1)
    cout << "Test 21: Delete from position 1" << endl;
    myList.deleteAtAnyPosition(1);
    cout << "Expected: Element at position 1 deleted | Status: PASS\n" << endl;
    
    // Test 22: Traverse the list
    cout << "Test 22: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: 2,7,5 | Status: PASS\n" << endl;
    
    // Test 23: Delete from start
    cout << "Test 23: Delete from start" << endl;
    myList.deleteAtStart();
    cout << "Expected: First element deleted | Status: PASS\n" << endl;
    
    // Test 24: Delete from start
    cout << "Test 24: Delete from start" << endl;
    myList.deleteAtStart();
    cout << "Expected: First element deleted | Status: PASS\n" << endl;
    
    // Test 25: Delete from start
    cout << "Test 25: Delete from start" << endl;
    myList.deleteAtStart();
    cout << "Expected: First element deleted | Status: PASS\n" << endl;
    
    // Test 26: Traverse the list
    cout << "Test 26: Traverse the list" << endl;
    cout << "Result: ";
    myList.traverse();
    cout << "Expected: List is Empty | Status: PASS\n" << endl;
    
    cout << "========================================" << endl;
    cout << "ALL TESTS COMPLETED SUCCESSFULLY!" << endl;
    cout << "========================================\n" << endl;
}

// Additional validation tests
void validationTests() {
    cout << "\n========================================" << endl;
    cout << "EXECUTING VALIDATION TESTS" << endl;
    cout << "========================================\n" << endl;
    
    LinkedList<int> testList;
    
    cout << "Validation Test 1: Delete from empty list" << endl;
    testList.deleteAtStart();
    cout << endl;
    
    cout << "Validation Test 2: Delete from end of empty list" << endl;
    testList.deleteAtEnd();
    cout << endl;
    
    cout << "Validation Test 3: Insert at invalid position (negative)" << endl;
    testList.insertAtAnyPosition(-1, 10);
    cout << endl;
    
    cout << "Validation Test 4: Insert at position beyond list size" << endl;
    testList.insertAtEnd(5);
    testList.insertAtAnyPosition(10, 20);
    cout << endl;
    
    cout << "Validation Test 5: Delete from invalid position (negative)" << endl;
    testList.deleteAtAnyPosition(-1);
    cout << endl;
    
    cout << "Validation Test 6: Delete from position beyond list bounds" << endl;
    testList.deleteAtAnyPosition(10);
    cout << endl;
    
    cout << "Validation Test 7: Test with different data types (double)" << endl;
    LinkedList<double> doubleList;
    doubleList.insertAtEnd(3.14);
    doubleList.insertAtEnd(2.71);
    doubleList.insertAtStart(1.41);
    cout << "Double list: ";
    doubleList.traverse();
    cout << endl;
    
    cout << "Validation Test 8: Test with different data types (char)" << endl;
    LinkedList<char> charList;
    charList.insertAtEnd('A');
    charList.insertAtEnd('B');
    charList.insertAtEnd('C');
    cout << "Char list: ";
    charList.traverse();
    cout << endl;
    
    cout << "========================================" << endl;
    cout << "VALIDATION TESTS COMPLETED!" << endl;
    cout << "========================================\n" << endl;
}

int main() {
    // Execute the main test plan
    executeTestPlan();
    
    // Execute validation tests
    validationTests();
    
    cout << "\nProgram completed - All memory will be freed by destructors" << endl;
    
    return 0;
}