#include <bits/stdc++.h>
#include "huffman.h"
using namespace std;

int main() {
    HuffmanTree huffman;
    
    string input = "video.mp4";   // Arquivo original
    string compressed = "video.huff";  // Arquivo compactado
    string decompressed = "output.mp4"; // Arquivo descompactado

    huffman.compress(input, compressed);
    cout << "Arquivo compactado: " << compressed << endl;

    huffman.decompress(compressed, decompressed);
    cout << "Arquivo descompactado: " << decompressed << endl;

    return 0;
}