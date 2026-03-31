#include <iostream>
#include <string>
using namespace std;

struct HTNode {
    string  key;
    string  value;
    HTNode* next;

    HTNode(const string& k, const string& v)
        : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 17; 
    HTNode* table[TABLE_SIZE];
    int     count;

    int hashFunction(const string& key) const {
        unsigned long hash = 0;
        for (int i = 0; i < (int)key.size(); i++)
            hash = hash * 31 + (unsigned char)key[i];
        return (int)(hash % TABLE_SIZE);
    }

public:
    HashTable() : count(0) {
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HTNode* curr = table[i];
            while (curr) {
                HTNode* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
            table[i] = nullptr;
        }
    }

    bool insert(const string& key, const string& value) {
        int idx = hashFunction(key);

        HTNode* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                curr->value = value; // update
                cout << "[*] Key \"" << key << "\" updated.\n";
                return true;
            }
            curr = curr->next;
        }

        HTNode* node = new HTNode(key, value);
        node->next   = table[idx];
        table[idx]   = node;
        count++;
        return true;
    }

    bool remove(const string& key) {
        int     idx  = hashFunction(key);
        HTNode* curr = table[idx];
        HTNode* prev = nullptr;

        while (curr) {
            if (curr->key == key) {
                if (prev) prev->next  = curr->next;
                else       table[idx] = curr->next;
                delete curr;
                count--;
                cout << "[*] Key \"" << key << "\" deleted.\n";
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "[!] Key \"" << key << "\" not found.\n";
        return false;
    }

    string search(const string& key) const {
        int     idx  = hashFunction(key);
        HTNode* curr = table[idx];

        while (curr) {
            if (curr->key == key)
                return curr->value;
            curr = curr->next;
        }
        return "";
    }

    void display() const {
        cout << "\n[*] Hash Table (" << count << " entries):\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i]) continue;
            cout << "  [" << i << "] -> ";
            HTNode* curr = table[i];
            while (curr) {
                cout << "(" << curr->key << " : " << curr->value << ")";
                if (curr->next) cout << " -> ";
                curr = curr->next;
            }
            cout << "\n";
        }
    }

    int getCount() const { return count; }
};

template <typename T>
T getInput(const string& prompt) {
    T val;
    do {
        cout << prompt;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[!] Invalid input. Try again.\n";
        } else break;
    } while (true);
    cin.ignore(1000, '\n');
    return val;
}
