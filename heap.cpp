#include "heap.hpp"
#include "huffman.hpp"
#include <algorithm>

template<typename T>
MinHeap<T>::MinHeap() {}

template<typename T>
int MinHeap<T>::parent(int i) { return (i - 1) / 2; }

template<typename T>
int MinHeap<T>::leftChild(int i) { return 2 * i + 1; }

template<typename T>
int MinHeap<T>::rightChild(int i) { return 2 * i + 2; }

template<typename T>
void MinHeap<T>::heapifyUp(int i) {
    while (i > 0 && heap[i] < heap[parent(i)]) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

template<typename T>
void MinHeap<T>::heapifyDown(int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap.size() && heap[left] < heap[smallest])
        smallest = left;
    if (right < heap.size() && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        std::swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

template<typename T>
void MinHeap<T>::push(T value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

template<typename T>
void MinHeap<T>::pop() {
    if (heap.empty()) return;
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
}

template<typename T>
T MinHeap<T>::top() const {
    if (!heap.empty()) return heap[0];
    throw std::runtime_error("Heap vazio!");
}

template<typename T>
bool MinHeap<T>::empty() const {
    return heap.empty();
}

template<typename T>
size_t MinHeap<T>::size() const {
    return heap.size();
}

// ***** Instanciações explícitas do template *****
template class MinHeap<int>;  // Se for usar MinHeap<int>, instancie aqui
template class MinHeap<float>; // Se precisar de float, adicione também
template class MinHeap<double>; // Se precisar de double, adicione também
template class MinHeap<HuffmanTree::Node*>;  // Adicione esta linha para corrigir o erro!