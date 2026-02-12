#include <iostream>
using namespace std;

struct Task {
    int taskID;
    int workUnits;
    void display() const {
        cout << "ID: " << taskID << " - Work: " << workUnits << endl;
    }
};

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

public:
    DoublyLinkedList() { head = tail = nullptr; }

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
    }
    bool isEmpty() { return (head == nullptr); }
    void display() {
        if (isEmpty()) { 
            cout << "Empty!" << endl; 
            return; 
        }
        node* temp = head;
        while (temp != nullptr) {
            temp->data.display(); 
            cout << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

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

    bool isEmpty() { return (front == nullptr); } 
    void enqueue(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->next = nullptr;
        if (front == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    void dequeue() {
        if (front == nullptr) return;
        node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
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
            temp->data.display();  
            cout << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class System {
private:
    DynamicQueue<Task> waitingTasks;
    DoublyLinkedList<Task> completedTasks;
    Task* currentTask;

public:
    System() {
        currentTask = nullptr;
    }
    ~System() {
        if (currentTask != nullptr) {
            delete currentTask;
        }
    }
    
//-----------------------------------------------------------

    void addTask(int id, int work) {
        Task t = {id, work}; 
        waitingTasks.enqueue(t);
        cout << "Task " << id << " added to the system." << endl;
    }
    void processStep() {
        if (currentTask == nullptr) {
            currentTask = new Task(waitingTasks.getFront()); 
            waitingTasks.dequeue();
            cout << "Processor is working on new task: " << currentTask->taskID << endl;
        }
        
        currentTask->workUnits--;   

        cout << "Processed 1 unit of Task " << currentTask->taskID << ". Remaining: " << currentTask->workUnits << endl;
        if (currentTask->workUnits <= 0) {
            cout << "Task " << currentTask->taskID << " completed" << endl;
            completedTasks.insertAtEnd(*currentTask);
            delete currentTask;
            currentTask = nullptr;
        }
    }
    void showCurrentTask() {
            cout << "Currently Handling: ";
            currentTask->display();  
            cout << endl;
    }
    void showWaitingTasks() {
        cout << "Waiting Tasks: ";
        waitingTasks.display();
    }
    void showCompletedTasks() {
        cout << "Completed Tasks Record: ";
        completedTasks.display();
    }
    void processAll() {
        while (!waitingTasks.isEmpty() || currentTask != nullptr) {
            processStep();
        }
        cout << "all tasks processed." << endl;
    }
};

int main() {
    System sys;
    int choice, id, work;

    do {
        cout << "\n~~~ Computing System ~~~" << endl;
        cout << "1. Add New Task" << endl;
        cout << "2. Process One Step" << endl;
        cout << "3. Show Current Task" << endl;
        cout << "4. Show Waiting Tasks" << endl;
        cout << "5. Show Completed Tasks" << endl;
        cout << "6. Process All Remaining Tasks" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: "; 
                cin >> id;
                cout << "Enter Work Units: "; 
                cin >> work;
                sys.addTask(id, work);
                break;
            case 2:
                sys.processStep();
                break;
            case 3:
                sys.showCurrentTask();
                break;
            case 4:
                sys.showWaitingTasks();
                break;
            case 5:
                sys.showCompletedTasks();
                break;
            case 6:
                sys.processAll();
                break;
            case 0:
                cout << "Exiting tthe system" << endl;
                break;
            default:
                cout << "invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}