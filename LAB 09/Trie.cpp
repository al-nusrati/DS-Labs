#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> m;
    bool flag;
    TrieNode() : flag(false) {}
};

class Trie {
    TrieNode* root;

    string toLower(const string& s) {
        string res = s;
        transform(res.begin(), res.end(), res.begin(), ::tolower);
        return res;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        string word;
        if (file.is_open()) {
            while (getline(file, word)) {
                if (!word.empty() && word.back() == '\r') word.pop_back();
                if (!word.empty()) {
                    insertTrie(toLower(word));
                }
            }
            file.close();
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    void insertTrie(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (cur->m.find(c) == cur->m.end())
                cur->m[c] = new TrieNode();
            cur = cur->m[c];
        }
        cur->flag = true;
    }

    void suggest(string prefix) {
        string lower = toLower(prefix);
        TrieNode* cur = root;
        for (char c : lower) {
            if (cur->m.find(c) == cur->m.end()) {
                cout << "  No suggestions found for \"" << prefix << "\"" << endl;
                return;
            }
            cur = cur->m[c];
        }

        list<string> results;
        string current = lower;
        retrieveHelper(cur, current, results);

        if (results.empty()) {
            cout << "  No suggestions found for \"" << prefix << "\"" << endl;
            return;
        }

        int count = 0;
        for (string w : results) {
            if (count >= 5) break;
            cout << "  -> " << w << endl;
            count++;
        }
    }

private:
    void retrieveHelper(TrieNode* node, string& current, list<string>& allWords) {
        if (!node) return;
        if (node->flag) {
            allWords.push_back(current);
        }
        for (auto pair : node->m) {
            current += pair.first;
            retrieveHelper(pair.second, current, allWords);
            current.pop_back();
        }
    }
};

int main() {
    Trie t;
    t.loadFromFile(R"(C:\Users\Jawad\Desktop\Labs\DS\words.txt)");
    cout << "Dictionary loaded.\n\n";

    string testPrefixes[] = { "app", "ban", "cat", "z" };
    for (string prefix : testPrefixes) {
        cout << "Prefix \"" << prefix << "\":" << endl;
        t.suggest(prefix);
        cout << endl;
    }

    string input;
    while (true) {
        cout << "Enter prefix (0 to exit): ";
        cin >> input;
        if (input == "0") break;
        t.suggest(input);
        cout << endl;
    }

    return 0;
}