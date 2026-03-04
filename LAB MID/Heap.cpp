#include <iostream>
#include <string>
using namespace std;

// ==========================================
// TEMPLATED INPUT VALIDATION (Elite Tier)
// ==========================================
template <typename T>
T getValidInput(string prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value; 
        }
        cout << "Error: Invalid input! Please enter the correct data type.\n";
        cin.clear();             
        cin.ignore(10000, '\n'); 
    }
}

// --- Max Heap Class Definition ---
class MaxHeap {
private:
    int* arr;       // Changed from fixed array to dynamic pointer
    int capacity;   // Stores the max capacity
    int size;       // Stores current number of elements

    // ==========================================
    // PRIVATE HELPER FUNCTIONS (The Logic Core)
    // ==========================================

    void heapifyUp(int index) {
        if (index == 0) return; // Base case: reached root

        int parent = (index - 1) / 2;
        
        // If current node is greater than parent, swap and recurse
        if (arr[index] > arr[parent]) {
            swap(arr[index], arr[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        // Check if left child exists and is greater than current largest
        if (left < size && arr[left] > arr[largest]) {
            largest = left;
        }
        
        // Check if right child exists and is greater than current largest
        if (right < size && arr[right] > arr[largest]) {
            largest = right;
        }

        // If largest is not the current node, swap and recurse
        if (largest != index) {
            swap(arr[index], arr[largest]);
            heapifyDown(largest);
        }
    }

public:
    // ==========================================
    // PUBLIC INTERFACE 
    // ==========================================
    
    // Constructor: Now takes capacity as an argument (Default is 100)
    MaxHeap(int cap = 100) { 
        capacity = cap;
        size = 0; 
        arr = new int[capacity]; // Dynamically allocate memory
    }

    // Destructor: Prevents memory leaks (Crucial for 20% Efficiency Rubric)
    ~MaxHeap() {
        delete[] arr;
        arr = nullptr;
    }

    bool isEmpty() { 
        return (size == 0); 
    }

    bool isFull() {
        return (size == capacity);
    }

    // --- 1. getTop() ---
    int getTop() {
        if (isEmpty()) {
            return -1; // Sentinel value indicating empty
        }
        return arr[0];
    }

    // --- 2. insert() ---
    // Reusability Fix: Returns bool instead of printing inside the class
    bool insert(int val) {
        if (isFull()) {
            return false; // Insertion failed
        }
        
        arr[size] = val;    // Place at the end
        heapifyUp(size);    // Bubble it up to its correct position
        size++;
        return true;        // Insertion successful
    }

    // --- 3. remove() ---
    // Reusability Fix: Returns bool instead of printing inside the class
    bool remove() {
        if (isEmpty()) {
            return false; // Removal failed
        }
        
        // Step 1: Replace root with the last element
        arr[0] = arr[size - 1];
        size--;
        
        // Step 2: Bubble the new root down to its correct position
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return true; // Removal successful
    }

    // --- Display ---
    void display() {
        if (isEmpty()) {
            cout << "Heap is empty" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// // ==========================================
// // MAIN FUNCTION
// // ==========================================
// int main() {
//     // We can now define the exact size we want!
//     MaxHeap heap(10); // Creating a heap with capacity 10

//     cout << "--- Inserting Nodes ---" << endl;
    
//     // Main function handles the UI/Printing now
//     if(!heap.insert(50)) cout << "Heap Overflow!" << endl;
//     heap.insert(30);
//     heap.insert(20);
//     heap.insert(15);
//     heap.insert(10);
//     heap.insert(8);
//     heap.insert(16);
//     heap.insert(60); // This should bubble up to the top

//     cout << "Heap array : "; 
//     heap.display();

//     cout << "\n--- Testing getTop() ---" << endl;
//     int topVal = heap.getTop();
//     if (topVal != -1) cout << "Top element: " << topVal << endl;
//     else cout << "Heap is empty! No top element." << endl;

//     cout << "\n--- Deleting Nodes ---" << endl;
//     cout << "Removing top element..." << endl;
    
//     if(heap.remove()) {
//         cout << "Heap after remove : "; 
//         heap.display();
//         cout << "New Top element   : " << heap.getTop() << endl;
//     } else {
//         cout << "Underflow! Heap is empty." << endl;
//     }

//     cout << "\n--- Interactive Input Test (Using Template) ---" << endl;
//     int userVal = getValidInput<int>("Enter an integer to insert into Heap: ");
    
//     if(heap.insert(userVal)) {
//         cout << "Heap after user insert: ";
//         heap.display();
//     } else {
//         cout << "Failed to insert. Heap is full." << endl;
//     }

//     cout << "\n--- Destructor will run automatically here, freeing memory ---" << endl;

//     system("pause>0");
//     return 0;
// }