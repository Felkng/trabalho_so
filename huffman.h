#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <bits/stdc++.h>
using namespace std;

class HuffmanTree {
private:
    struct Node {
        unsigned char data;
        int freq;
        Node *left, *right;

        Node(unsigned char d, int f);
    };

    struct Compare {
        bool operator()(Node* a, Node* b);
    };

    unordered_map<unsigned char, string> huffmanCodes;
    Node* root;

    Node* buildTree(const vector<int>& freq_table);
    void generateCodes(Node* root, string code);
    void freeTree(Node* node);

public:
    HuffmanTree();
    ~HuffmanTree();
    void compress(const string &inputFile, const string &outputFile);
    void decompress(const string &inputFile, const string &outputFile);
};

#endif