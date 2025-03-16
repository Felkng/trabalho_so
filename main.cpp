#include <bits/stdc++.h>
#include "huffman.h"
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Uso incorreto. Sintaxe: <C|D> <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }

    string mode = argv[1];
    string input = argv[2];
    string output = argv[3];

    HuffmanTree huffman;

    if (mode == "C") {
        // Compressão
        auto inicio = std::chrono::high_resolution_clock::now();
        
        huffman.compress(input, output);
        
        cout << "Arquivo compactado: " << output << endl;
        
        auto fim = std::chrono::high_resolution_clock::now();
        auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
        cout << "Compressão: " << duracao.count()/1000 << "s" << endl;
    } else if (mode == "D") {
        // Descompressão
        string decompressed = output;
        auto inicio = std::chrono::high_resolution_clock::now();
        
        huffman.decompress(input, decompressed);
        
        cout << "Arquivo descompactado: " << decompressed << endl;
        
        auto fim = std::chrono::high_resolution_clock::now();
        auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
        cout << "Descompressão: " << duracao.count()/1000 << "s" << endl;
    } else {
        cerr << "Modo desconhecido: " << mode << ". Use 'C' para compressão ou 'D' para descompressão." << endl;
        return 1;
    }

    return 0;
}
