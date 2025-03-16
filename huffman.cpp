#include "huffman.h"

HuffmanTree::Node::Node(unsigned char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}

bool HuffmanTree::Compare::operator()(Node* a, Node* b) {
    return a->freq > b->freq;
}

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree() {
    freeTree(root);
}

HuffmanTree::Node* HuffmanTree::buildTree(const vector<int>& freq_table) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (int i = 0; i < 256; i++) {
        if (freq_table[i] > 0) {
            minHeap.push(new Node((unsigned char)i, freq_table[i]));
        }
    }

    while (minHeap.size() > 1) {
        Node *left = minHeap.top(); minHeap.pop();
        Node *right = minHeap.top(); minHeap.pop();
        Node *newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }
    return minHeap.top();
}

void HuffmanTree::generateCodes(Node* root, string code) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }
    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

void HuffmanTree::freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

void HuffmanTree::compress(const string &inputFile, const string &outputFile) {
    ifstream file(inputFile, ios::binary);
    if (!file) {
        cerr << "Erro ao abrir " << inputFile << endl;
        return;
    }

    vector<int> freq_table(256, 0);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    for (unsigned char c : content) {
        freq_table[c]++;
    }
    file.close();

    root = buildTree(freq_table);
    generateCodes(root, "");

    string resultPath = outputFile;
    ofstream output(resultPath, ios::binary);
    if (!output) {
        cerr << "Erro ao criar arquivo " << resultPath << endl;
        return;
    }

    for (int f : freq_table) {
        output.write(reinterpret_cast<char*>(&f), sizeof(int));
    }

    string encodedStr = "";
    for (unsigned char c : content) {
        encodedStr += huffmanCodes[c];
    }

    while (encodedStr.size() % 8 != 0) {
        encodedStr += "0";
    }

    for (size_t i = 0; i < encodedStr.size(); i += 8) {
        bitset<8> byte(encodedStr.substr(i, 8));
        unsigned char byteVal = static_cast<unsigned char>(byte.to_ulong());
        output.write(reinterpret_cast<char*>(&byteVal), sizeof(unsigned char));
    }

    output.close();
}

void HuffmanTree::decompress(const string &inputFile, const string &outputFile) {
    ifstream input(inputFile, ios::binary);
    if (!input) {
        cerr << "Erro ao abrir " << inputFile << endl;
        return;
    }

    vector<int> freq_table(256, 0);
    for (int i = 0; i < 256; i++) {
        input.read(reinterpret_cast<char*>(&freq_table[i]), sizeof(int));
    }

    root = buildTree(freq_table);

    string bitString = "";
    unsigned char byte;
    while (input.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char))) {
        bitString += bitset<8>(byte).to_string();
    }
    input.close();

    string resultPath = outputFile;
    ofstream output(resultPath, ios::binary);
    if (!output) {
        cerr << "Erro ao criar arquivo " << resultPath << endl;
        return;
    }

    Node* curr = root;
    for (char bit : bitString) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            output.put(curr->data);
            curr = root;
        }
    }

    output.close();
}