#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &a, int ini, int fim) {
    int pivo = a[fim];
    int i = ini - 1;
    for (int j = ini; j < fim; j++) {
        if (a[j] < pivo) {
            i++;
            swap(a[j], a[i]);
        }
    }
    i++;
    swap(a[i], a[fim]);
    return i;
}

void quicksort(vector<int> &a, int ini, int fim) {
    if (ini < fim) {
        int j = partition(a, ini, fim);
        quicksort(a, ini, j - 1);
        quicksort(a, j + 1, fim);
    }
}

int main() {
    vector<int> frequency_table;
    frequency_table.resize(256, 0);
    string video = "video.mp4";

    ifstream file(video, ios::binary);
    
    if(!file){
        cerr << "Não foi possível abrir o arquivo";
        return 1;
    }


    file.seekg(0, ios::end);
    streamsize file_size = file.tellg();
    file.seekg(0, ios::beg);

    vector<unsigned char> buffer(file_size);

    if(!file.read(reinterpret_cast<char*>(buffer.data()), file_size)){
        cerr << "Não foi possível ler o arquivo";
        return 1;
    }

    for (unsigned char c : buffer) {
        frequency_table[c]++;
    }

    quicksort(frequency_table, 0, frequency_table.size() - 1);
    
    for (int i = 0; i < frequency_table.size(); i++) cout << "caractere " << "'" << (char)i << "'" << " aparece " << frequency_table[i] << " vezes\n";
    cout << endl;
    
    return 0;
}
