#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
struct NodeDL {
    T value;
    NodeDL* next;
    NodeDL* previous;

    NodeDL(T v, NodeDL* n = nullptr, NodeDL* p = nullptr);
};

template <typename T>
struct DL_list {
    NodeDL<T>* head;
    NodeDL<T>* tail;
    int size;

    DL_list();
    DL_list(const DL_list& other);
    DL_list& operator=(const DL_list& other);
    ~DL_list();

    void clear();
};


template <typename T>
void addHeadDL(DL_list<T>& list, const T& value);

template <typename T>
void addTailDL(DL_list<T>& list, const T& value);

template <typename T>
void addAfterDL(DL_list<T>& list, int index, const T& value);

template <typename T>
void addBeforeDL(DL_list<T>& list, int index, const T& value);

template <typename T>
void removeByValueDL(DL_list<T>& list, const T& value);

template <typename T>
int searchByValueDL(DL_list<T>& list, const T& value);

template <typename T>
void printDL(DL_list<T>& list);

template <typename T>
void backwardsPrintDL(DL_list<T>& list);
