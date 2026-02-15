#include <iostream>
using namespace std;

struct Shape {
    int shapeID;
    string shapeType; 
    void display() const {
        cout << "ID: " << shapeID << " - Type: " << shapeType << endl;
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
    
    void deleteFromEnd() {
        if (tail == nullptr) {
            cout << "Empty List" << endl;
            return;
        }
        node* temp = tail;
        tail = tail->prev;
        if (tail == nullptr) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }
        delete temp;
    }
    
    bool isEmpty() { return (head == nullptr); }
    
    T getLastElement() {
        if (tail != nullptr) return tail->data;
        return T();
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Canvas is empty" << endl;
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
class DynamicStack {
private:
    struct node {
        T data;
        node* next;
    };
    node* top;

public:
    DynamicStack() { top = nullptr; }

    bool isEmpty() { return (top == nullptr); }

    void push(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) return;
        node* temp = top;
        top = top->next;
        delete temp;
    }

    T peek() {
        if (top != nullptr) return top->data;
        return T();
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        node* temp = top;
        while (temp != nullptr) {
            temp->data.display();
            cout << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~DynamicStack() {
        while (top != nullptr) {
            pop();
        }
    }
};

struct Action {
    string actionType; //--- either add or delete
    Shape shape;
    
    void display() const {
        cout << "Action: " << actionType << " - ";
        shape.display();
    }
};

class CanvasEditor {
private:
    DoublyLinkedList<Shape> canvas;
    DynamicStack<Action> undoStack;
    DynamicStack<Action> redoStack;

public:
    CanvasEditor() {}
    
    //-----------------------------------------------------------
    
    void addShape(int id, string type) {
        Shape s = {id, type};
        canvas.insertAtEnd(s);
        
        Action act;
        act.actionType = "ADD";
        act.shape = s;
        undoStack.push(act);
        
        redoStack.clear();
        
        cout << "Shape " << id <<  type << " added to canvas." << endl;
    }
    
    void deleteLastShape() {
        if (canvas.isEmpty()) {
            cout << "Canvas is empty - Nothing to delete." << endl;
            return;
        }
        
        Shape lastShape = canvas.getLastElement();
        canvas.deleteFromEnd();
        
        Action act;
        act.actionType = "DELETE";
        act.shape = lastShape;
        undoStack.push(act);
        
        redoStack.clear();
        
        cout << "Last shape (ID: " << lastShape.shapeID << ") deleted from canvas." << endl;
    }
    
    void undo() {
        if (undoStack.isEmpty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }
        
        Action lastAction = undoStack.peek();
        undoStack.pop();
        
        if (lastAction.actionType == "ADD") {
            canvas.deleteFromEnd();
            cout << "Undo: Removed shape (ID: " << lastAction.shape.shapeID << ")" << endl;
        } else if (lastAction.actionType == "DELETE") {
            canvas.insertAtEnd(lastAction.shape);
            cout << "Undo: Restored shape (ID: " << lastAction.shape.shapeID << ")" << endl;
        }
        
        redoStack.push(lastAction);
    }
    
    void redo() {
        if (redoStack.isEmpty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }
        
        Action lastUndone = redoStack.peek();
        redoStack.pop();
        
        if (lastUndone.actionType == "ADD") {
            canvas.insertAtEnd(lastUndone.shape);
            cout << "Redo: Added shape (ID: " << lastUndone.shape.shapeID << ") back" << endl;
        } else if (lastUndone.actionType == "DELETE") {
            canvas.deleteFromEnd();
            cout << "Redo: Deleted shape (ID: " << lastUndone.shape.shapeID << ") again" << endl;
        }
        
        undoStack.push(lastUndone);
    }
    
    void displayCanvas() {
        cout << "Current Canvas: ";
        canvas.display();
    }
};

int main() {
    CanvasEditor editor;
    int choice, id;
    string type;
    
    do {
        cout << "\n~~~ Canvas Editor ~~~" << endl;
        cout << "1. Add Shape" << endl;
        cout << "2. Delete Last Shape" << endl;
        cout << "3. Undo" << endl;
        cout << "4. Redo" << endl;
        cout << "5. Display Canvas" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter Shape ID: ";
                cin >> id;
                cout << "Enter Shape Type (Circle/Rectangle/TextBox): ";
                cin >> type;
                editor.addShape(id, type);
                break;
            case 2:
                editor.deleteLastShape();
                break;
            case 3:
                editor.undo();
                break;
            case 4:
                editor.redo();
                break;
            case 5:
                editor.displayCanvas();
                break;
            case 0:
                cout << "Exiting the editor" << endl;
                break;
            default:
                cout << "invalid choice" << endl;
        }
    } while (choice != 0);
    
    return 0;
}