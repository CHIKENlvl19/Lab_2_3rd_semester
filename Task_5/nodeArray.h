#pragma once

#include <iostream>

using namespace std;

template <typename T>
class NodeArray {
private:
    T** data;      // массив указателей на объекты типа T
    int size;
    int capacity;

    void resize() {
        int newCapacity = capacity * 2;
        T** newData = new T*[newCapacity];
        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }
            
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    NodeArray(int initialCapacity = 16)
        : size(0), capacity(initialCapacity) {
        data = new T*[capacity];
    }

    ~NodeArray() {
        delete[] data;
    }

    void add(T* node) {
        if (size == capacity)
        {
            resize();
        }
            
        data[size++] = node;
    }

    // Извлекает указатель на элемент с минимальным полем freq
    T* extractMin() {
        if (size == 0) return nullptr;

        int minIndex = 0;
        for (int i = 1; i < size; ++i) 
        {
            if (data[i]->freq < data[minIndex]->freq ||
                (data[i]->freq == data[minIndex]->freq && data[i]->symbol < data[minIndex]->symbol))
            {
                minIndex = i;
            }
        }

        T* minNode = data[minIndex];
        for (int i = minIndex; i < size - 1; ++i)
        {
            data[i] = data[i + 1];
        }
            
        size--;
        return minNode;
    }

    int getSize() const {
        return size;
    }

    void print() const {
        cout << "Список узлов: ";
        for (int i = 0; i < size; ++i)
        {
            cout << data[i]->symbol << "(" << data[i]->freq << ") ";
        }
            
        cout << endl;
    }
};