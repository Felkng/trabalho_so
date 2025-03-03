#include <bits/stdc++.h>
#include "huffman.h"
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;


void createDirectoryIfNotExists(const string &dir) {
    struct stat st = {0};
    if (stat(dir.c_str(), &st) == -1) {
        mkdir(dir.c_str(), 0700);  // Cria a pasta 'result' caso não exista
    }
}

int main() {
    HuffmanTree huffman;
    
    string input = "lalala.pdf";   // Arquivo original
    string compressed = "file.huff";  // Arquivo compactado
    string decompressed = "output_" + input.substr(0, input.find_last_of(".")) + input.substr(input.find_last_of("."));
    createDirectoryIfNotExists("result");

    huffman.compress(input, compressed);
    cout << "Arquivo compactado: " << compressed << endl;

    huffman.decompress("result/"+compressed, decompressed);
    cout << "Arquivo descompactado: " << decompressed << endl;

    return 0;
}