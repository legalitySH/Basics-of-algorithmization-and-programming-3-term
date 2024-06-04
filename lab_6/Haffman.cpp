#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// A Tree node
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Comparison object to be used to order the heap
struct comp {
	bool operator()(Node* l, Node* r) {
		// highest priority item has lowest frequency
		// if frequencies are equal, compare characters based on their order in the string
		return (l->freq > r->freq) || (l->freq == r->freq && l->ch > r->ch);
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void printHuffmanTree(Node* root, string indent = "") {
	if (root == nullptr)
		return;

	// Print information about the current node
	cout << indent;
	if (root->ch != '\0') {
		cout << "Символ: " << root->ch << ", Частота: " << root->freq << endl;
	}
	else {
		cout << "Внутренний узел, Частота: " << root->freq << endl;
	}

	// Print left and right subtrees
	printHuffmanTree(root->left, indent + "  (л) ");
	printHuffmanTree(root->right, indent + "  (п) ");
}


// traverse the Huffman Tree and decode the encoded string
void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

// Builds Huffman Tree and decode given input text
void buildHuffmanTree(string text)
{
	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	priority_queue<Node*, vector<Node*>, comp> pq_copy(pq);
	cout << "Исходная строка \"" << text << "\"" << endl;
	cout << "Очередь с приоритетом:" << endl;
	while (!pq_copy.empty()) {
		Node* node = pq_copy.top();
		cout << "Символ: " << node->ch << ", Частота: " << node->freq << endl;
		pq_copy.pop();
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	Node* root = pq.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);
	printHuffmanTree(root);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	// traverse the Huffman Tree again and this time
	// decode the encoded string
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}

// Huffman coding algorithm
int main()
{
	setlocale(LC_ALL, "rus");
	string text = "соснаволосна";

	

	buildHuffmanTree(text);
	

	return 0;
}