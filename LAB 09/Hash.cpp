#include <iostream>
#include <list>
#include <string>
using namespace std;

class HashMap {
private:
    static const int hashIndexes = 10;
    list<pair<string, string>> ArrLinkedList[hashIndexes];  //array of linked lists

    int hashFunction(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++) {  //sum of ASCII values of each char
            sum += key[i];
        }
        return sum % hashIndexes;
    }

public:

    void insert(string key, string value) {
        int index = hashFunction(key);
        for (auto it = ArrLinkedList[index].begin(); it != ArrLinkedList[index].end(); it++) {
            if (it->first == key) {    //this checks if key already exists or not. if it does then it updates 'value' of that 'key'.
                it->second = value;
                cout << "Key " << key << " updated to " << value << "\n";
                return; 
            }
        }
        ArrLinkedList[index].push_back({key, value});   //this is add new key value pair to the end of the linked list at that index.
        cout << "Inserted (" << key << ", " << value << ") at index " << index << "\n";
    }

    void deleteItem(string key) {
        int index = hashFunction(key);
        for (auto it = ArrLinkedList[index].begin(); it != ArrLinkedList[index].end(); it++) {      //no array , used iterator to traverse the linked list at that index as memory is scattered
            if (it->first == key) {
                ArrLinkedList[index].erase(it); // i. deletes ii. shifts the rest of the elements in the linked list to fill the gap left iii. frees the memory of the deleted node.
                cout << "Key " << key << " deleted.\n";
                return;
            }
        }
        cout << "Key " << key << " not found. Nothing deleted.\n";
    }

    bool search(string key, string& retrievedValue) {  // returns true/false, fills retrievedValue for login comparison
        int index = hashFunction(key);
        for (auto it = ArrLinkedList[index].begin(); it != ArrLinkedList[index].end(); it++) {
            if (it->first == key) {
                retrievedValue = it->second;
                return true;
            }
        }
        return false;
    }

    void display() {
        cout << "\n--- Hash Table State ---\n";
        for (int i = 0; i < hashIndexes; i++) {
            cout << "Bucket [" << i << "]: ";
            if (ArrLinkedList[i].empty()) {
                cout << "empty";
            } else {
                for (auto& pair : ArrLinkedList[i]) {
                    cout << "(" << pair.first << ", " << pair.second << ") -> ";
                }
                cout << "NULL";
            }
            cout << "\n";
        }
    }

    bool isEmpty() {
        for (int i = 0; i < hashIndexes; i++) { //iterating through all indexes of the hash array
            if (!ArrLinkedList[i].empty()) {
                return false;
            }
        }
        return true;
    }

};

