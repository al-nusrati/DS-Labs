#include <iostream>
using namespace std;

#define CAPACITY 100

// --- Max Heap Class Definition ---
class MaxHeap {
private:
    int arr[CAPACITY];
    int size; 

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
    
    MaxHeap() { 
        size = 0; 
    }

    bool isEmpty() { 
        return (size == 0); 
    }

    bool isFull() {
        return (size == CAPACITY);
    }

    // --- 1. getTop() ---
    int getTop() {
        if (isEmpty()) {
            cout << "Heap is empty! No top element." << endl;
            return -1; // Return a sentinel value or throw exception
        }
        return arr[0];
    }

    // --- 2. insert() ---
    void insert(int val) {
        if (isFull()) {
            cout << "Overflow! Heap is full." << endl;
            return;
        }
        
        arr[size] = val;    // Place at the end
        heapifyUp(size);    // Bubble it up to its correct position
        size++;
    }

    // --- 3. remove() ---
    void remove() {
        if (isEmpty()) {
            cout << "Underflow! Heap is empty." << endl;
            return;
        }
        
        // Step 1: Replace root with the last element
        arr[0] = arr[size - 1];
        size--;
        
        // Step 2: Bubble the new root down to its correct position
        if (!isEmpty()) {
            heapifyDown(0);
        }
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

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    MaxHeap heap;

    cout << "--- Inserting Nodes ---" << endl;
    heap.insert(50);
    heap.insert(30);
    heap.insert(20);
    heap.insert(15);
    heap.insert(10);
    heap.insert(8);
    heap.insert(16);
    heap.insert(60); // This should bubble up to the top

    cout << "Heap array : "; 
    heap.display();

    cout << "\n--- Testing getTop() ---" << endl;
    cout << "Top element: " << heap.getTop() << endl;

    cout << "\n--- Deleting Nodes ---" << endl;
    cout << "Removing top element (" << heap.getTop() << ")" << endl;
    heap.remove();
    
    cout << "Heap after remove : "; 
    heap.display();
    cout << "New Top element   : " << heap.getTop() << endl;

    system("pause>0");
    return 0;
}