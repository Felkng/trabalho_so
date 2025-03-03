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
    
    string input = "video.mp4";   // Arquivo original
    string compressed = "video.huff";  // Arquivo compactado
    string decompressed = "output.mp4"; // Arquivo descompactado
    createDirectoryIfNotExists("result");

    huffman.compress(input, compressed);
    cout << "Arquivo compactado: " << compressed << endl;

    huffman.decompress(compressed, decompressed);
    cout << "Arquivo descompactado: " << decompressed << endl;

    return 0;
}