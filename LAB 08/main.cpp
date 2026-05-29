#include <iostream>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

struct HuffNode {
	char ch;
	int freq;
	HuffNode* left;
	HuffNode* right;

public:
	HuffNode(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
	HuffNode(char ch, int freq, HuffNode* left, HuffNode* right) : ch(ch), freq(freq), left(left), right(right) {}
	bool operator<(const HuffNode& other)const {
		return freq > other.freq;
	}
};

class Htree {
	unordered_map<char, int> freq;
	priority_queue<HuffNode> heap;
	string text;
	HuffNode* root = nullptr;

public:
	Htree(string file) {
		text = read(file);
		frequency(freq, text);;
		for (auto pair : freq) {
			heap.push(HuffNode(pair.first, pair.second));
		}

		while (heap.size() > 1) {
			HuffNode node1 = heap.top();
			heap.pop();

			HuffNode node2 = heap.top();
			heap.pop();

			HuffNode* left = new HuffNode(node1);
			HuffNode* right = new HuffNode(node2);
			HuffNode parent('\0', (node1.freq + node2.freq), left, right);

			heap.push(parent);

			root = new HuffNode(heap.top());
		}
	}
	
	void frequency(unordered_map<char, int>& freq, string str) {
		for (char c : str) {
			freq[c]++;
		}
	}

	void encodehelper(HuffNode* node, const string& code, string& str, char c) {
		if (!node) { return; }

		if (!node->left && !node->right) {
			if (c == node->ch) {
				str = code;
			}
			return;
		}

		encodehelper(node->left, code + "0", str, c);
		encodehelper(node->right, code + "1", str, c);
	}

	void encode() {

		string huffmancode = "";

		for (char c : text) {
			string Ccode = "";
			encodehelper(root, "", Ccode, c);
			huffmancode += Ccode;
		}

		cout << huffmancode << endl;
		write("D:\\encode.txt", huffmancode);
	}

	string decode() {
		string out;
		HuffNode* cur = root;
		string huffmancode = read("D:\\encode.txt");

		for (char b : huffmancode) {
			if (b == '0') { cur = cur->left; }
			else if (b == '1') { cur = cur->right; }

			if (!cur->left && !cur->right) {
				out += cur->ch;
				cur = root;
			}
		}
		write("D:\\decode.txt", out);
		return out;
	}

	string read(string filename) {
		ifstream file(filename);
		string text;

		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				text += line;
			}
			file.close();
		}

		else {
			cout << "Unable to open file" << endl;
		}
		return text;
	}

	void write(string encoded, string out) {
		ofstream MyFile(encoded);

		if (MyFile.is_open()) {
			MyFile << out;
			MyFile.close();
		}
		else {
			cout << "Unable to open file" << endl;
		}
	}
};

int main() {

	Htree t("D:\\input.txt");
	t.encode();
	cout << t.decode();
	return 0;
}