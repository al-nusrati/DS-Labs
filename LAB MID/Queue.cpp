#include <iostream>
#include <string>
using namespace std;



// ==================== DOUBLY LINKED LIST (Optimized Helper) ====================
template <typename T>
class DoublyLinkedList {
private:
    struct node {
        T data;
        node* next;
        node* prev;
    };
    node* head;
    node* tail;
    int size; // O(1) Size Tracking

public:
    DoublyLinkedList() {
        head = tail = nullptr;
        size = 0;
    }

    ~DoublyLinkedList() {
        while (!isEmpty()) {
            deleteFromStart();
        }
    }

    void insertAtBeginning(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->prev = nullptr;
        newNode->next = head;
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insertAtEnd(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->next = nullptr;
        newNode->prev = tail;
        
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    bool deleteFromStart() {
        if (head == nullptr) return false;
        
        node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }
        delete temp;
        size--;
        return true;
    }

    bool isEmpty() { return (size == 0); }

    void display() {
        node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ==================== 1. CIRCULAR QUEUE (Array-Based) ====================
template <typename T>
class CircularQueue {
private:
    T* queue; // Dynamic Array
    int front, rear;
    int capacity;
    int count;

public:
    CircularQueue(int cap = 5) {
        capacity = cap;
        queue = new T[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~CircularQueue() { delete[] queue; }

    bool isEmpty() { return (count == 0); }
    bool isFull() { return (count == capacity); }

    bool enqueue(T v) {
        if (isFull()) return false;
        rear = (rear + 1) % capacity;
        queue[rear] = v;
        count++;
        return true;
    }

    bool dequeue() {
        if (isEmpty()) return false;
        front = (front + 1) % capacity;
        count--;
        return true;
    }

    T getFront() {
        if (!isEmpty()) return queue[front];
        return T();
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        int i = front;
        int items = 0;
        while (items < count) {
            cout << queue[i] << " ";
            i = (i + 1) % capacity;
            items++;
        }
        cout << endl;
    }
};

// ==================== 2. DYNAMIC QUEUE (Singly Linked List) ====================
template <typename T>
class DynamicQueue {
private:
    struct node {
        T data;
        node* next;
    };
    node *front, *rear;

public:
    DynamicQueue() { front = rear = nullptr; }

    ~DynamicQueue() {
        while (!isEmpty()) dequeue();
    }

    bool isEmpty() { return (front == nullptr); }

    void enqueue(T x) {
        node* newNode = new node;
        newNode->data = x;
        newNode->next = nullptr;
        
        if (front == nullptr && rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    bool dequeue() {
        if (front == nullptr) return false;
        
        node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return true;
    }

    T getFront() {
        if (front != nullptr) return front->data;
        return T();
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ==================== 3. DYNAMIC QUEUE (Using DLL Adapter) ====================
template <typename T>
class QueueUsingList {
private:
    DoublyLinkedList<T> list;
public:
    void enqueue(T val) { list.insertAtEnd(val); }
    bool dequeue() { return list.deleteFromStart(); }
    bool isEmpty() { return list.isEmpty(); }
    void display() { list.display(); }
};

// ==================== 4. ARRAY STACK (Dynamic Size) ====================
template <typename T>
class ArrayStack {
private:
    T* stack; // Dynamic Array
    int top;
    int capacity;

public:
    ArrayStack(int cap = 5) {
        capacity = cap;
        stack = new T[capacity];
        top = -1;
    }

    ~ArrayStack() { delete[] stack; }

    bool isEmpty() { return (top == -1); }
    bool isFull() { return (top == capacity - 1); }

    bool push(T data) {
        if (isFull()) return false;
        top++;
        stack[top] = data;
        return true;
    }

    bool pop() {
        if (isEmpty()) return false;
        top--;
        return true;
    }

    T peek() {
        if (!isEmpty()) return stack[top];
        return T();
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

// ==================== 5. DYNAMIC STACK (Singly Linked List) ====================
template <typename T>
class DynamicStack {
private:
    struct node {
        T data;
        node* next;
    };
    node* top;

public:
    DynamicStack() { top = nullptr; }

    ~DynamicStack() {
        while (!isEmpty()) pop();
    }

    bool isEmpty() { return (top == nullptr); }

    void push(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }

    bool pop() {
        if (isEmpty()) return false;
        node* temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    T peek() {
        if (top != nullptr) return top->data;
        return T();
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ==================== 6. DYNAMIC STACK (Using DLL Adapter) ====================
template <typename T>
class StackUsingList {
private:
    DoublyLinkedList<T> list;
public:
    void push(T val) { list.insertAtBeginning(val); }
    bool pop() { return list.deleteFromStart(); }
    bool isEmpty() { return list.isEmpty(); }
    void display() { list.display(); }
};

// ==========================================
// MAIN FUNCTION
// // ==========================================
// int main() {
//     cout << "========== TESTING CIRCULAR QUEUE (Array) ==========" << endl;
//     CircularQueue<int> cq(5); // Dynamically sized to 5
//     cq.enqueue(10); cq.enqueue(20); cq.enqueue(30); cq.enqueue(40); cq.enqueue(50);
//     cout << "After enqueuing 5 elements: "; cq.display();
    
//     if (!cq.enqueue(60)) cout << "Overflow caught successfully!" << endl;
    
//     cq.dequeue(); cq.dequeue();
//     cout << "After 2 dequeues: "; cq.display();
//     cq.enqueue(60); cq.enqueue(70);
//     cout << "After circular enqueues: "; cq.display();

//     cout << "\n========== TESTING DYNAMIC QUEUE (Linked List) ==========" << endl;
//     DynamicQueue<int> dq;
//     dq.enqueue(100); dq.enqueue(200); dq.enqueue(300);
//     cout << "After enqueuing: "; dq.display();
//     dq.dequeue();
//     cout << "After dequeue: "; dq.display();

//     cout << "\n========== TESTING ARRAY STACK ==========" << endl;
//     ArrayStack<int> as(5); // Dynamically sized to 5
//     as.push(1); as.push(2); as.push(3); as.push(4); as.push(5);
//     cout << "After pushing 5 elements: "; as.display();
    
//     if (!as.push(6)) cout << "Stack Overflow caught successfully!" << endl;
    
//     cout << "Top element: " << as.peek() << endl;
//     as.pop(); as.pop();
//     cout << "After 2 pops: "; as.display();

//     cout << "\n========== TESTING DYNAMIC STACK (Linked List) ==========" << endl;
//     DynamicStack<int> ds;
//     ds.push(99); ds.push(88); ds.push(77);
//     cout << "After pushing: "; ds.display();
//     cout << "Top element: " << ds.peek() << endl;
//     ds.pop();
//     cout << "After pop: "; ds.display();

//     cout << "\n========== INTERACTIVE INPUT TEST (For Rubric) ==========" << endl;
//     int userVal = getValidInput<int>("Enter an integer to push to Dynamic Stack: ");
//     ds.push(userVal);
//     cout << "Stack after user input: "; ds.display();

//     cout << "\n--- Destructors will run automatically here, freeing all memory ---" << endl;
//     system("pause>0");
//     return 0;
// }