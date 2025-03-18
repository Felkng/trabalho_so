#ifndef HEAP_HPP
#define HEAP_HPP

#include <bits/stdc++.h>

template<typename T>
class MinHeap {
    private:
        std::vector<T> heap;

        int parent(int i);
        int leftChild(int i);
        int rightChild(int i);
        void heapifyUp(int i);
        void heapifyDown(int i);

    public:
        MinHeap();
        void push(T value);
        void pop();
        T top() const;
        bool empty() const;
        size_t size() const;
};

#endif