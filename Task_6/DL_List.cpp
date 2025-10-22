#include "DL_List.h"

using namespace std;


template <typename T>
NodeDL<T>::NodeDL(T v, NodeDL* n, NodeDL* p) : value(v), next(n), previous(p) {}

template <typename T>
DL_list<T>::DL_list() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DL_list<T>::DL_list(const DL_list& other) : head(nullptr), tail(nullptr), size(0) {
    NodeDL<T>* current = other.head;
    
    while(current) 
    {
        addTailDL(*this, current->value, "");
        current = current->next;
    }
}

template <typename T>
DL_list<T>& DL_list<T>::operator=(const DL_list& other) {
    if(this == &other) 
    {
        return *this;
    }

    clear();
    NodeDL<T>* current = other.head;
    while(current) 
    {
        addTailDL(*this, current->value, "");
        current = current->next;
    }

    return *this;
}

template <typename T>
DL_list<T>::~DL_list() { clear(); }

template <typename T>
void DL_list<T>::clear() {
    NodeDL<T>* current = head;
    
    while(current) 
    {
        NodeDL<T>* tmp = current;
        current = current->next;
        delete tmp;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}


template <typename T>
void addHeadDL(DL_list<T>& list, const T& value) {

    NodeDL<T>* newNode = new NodeDL<T>(value, list.head, nullptr);
    if(list.head) 
    {
        list.head->previous = newNode;
    } 
    else 
    {
        list.tail = newNode;
    }

    list.head = newNode;
    list.size++;
}

template <typename T>
void addTailDL(DL_list<T>& list, const T& value) {

    NodeDL<T>* newNode = new NodeDL<T>(value, nullptr, list.tail);
    if(list.tail) 
    {
        list.tail->next = newNode;
    }
    else
    {
        list.head = newNode;
    }

    list.tail = newNode;
    list.size++;
}

template <typename T>
void addAfterDL(DL_list<T>& list, int index, const T& value) {

    if(index < 0 || index >= list.size) 
    {
        cerr << "Error: index out of range in addAfterDL\n";
        return;
    }

    NodeDL<T>* current = list.head;
    for(int i = 0; i < index; i++)
    {
        current = current->next;
    }

    NodeDL<T>* newNode = new NodeDL<T>(value, current->next, current);
    if(current->next)
    {
        current->next->previous = newNode;
    }
    else
    {
        list.tail = newNode;
    }

    current->next = newNode;
    list.size++;
}

template <typename T>
void addBeforeDL(DL_list<T>& list, int index, const T& value) {

    if(index < 0 || index >= list.size) 
    {
        cerr << "Error: index out of range in addBeforeDL\n";
        return;
    }

    NodeDL<T>* current = list.head;
    for(int i = 0; i < index; i++)
    {
        current = current->next;
    }

    NodeDL<T>* newNode = new NodeDL<T>(value, current, current->previous);
    if(current->previous)
    {
        current->previous->next = newNode;
    }
    else
    {
        list.head = newNode;
    }

    current->previous = newNode;
    list.size++;
}


template <typename T>
void removeByValueDL(DL_list<T>& list, const T& value) {

    NodeDL<T>* current = list.head;
    while(current && current->value != value)
    {
        current = current->next;
    }

    if(!current) 
    {
        cerr << "Value not found in removeByValueDL\n";
        return;
    }

    if(current->previous)
    {
        current->previous->next = current->next;
    } else
    {
        list.head = current->next;
    }

    if(current->next)
    {
        current->next->previous = current->previous;
    }
    else
    {
        list.tail = current->previous;
    }

    delete current;
    list.size--;
}


template <typename T>
int searchByValueDL(DL_list<T>& list, const T& value) {

    NodeDL<T>* current = list.head;
    int index = 0;
    while(current)
    {
        if(current->value == value)
        {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}


template <typename T>
void printDL(DL_list<T>& list) {
    NodeDL<T>* current = list.head;

    cout << "[";
    while(current)
    {
        cout << current->value;
        if(current->next)
        {
            cout << " <-> ";
        }
        current = current->next;
    }
    cout << "]" << endl;
}

template <typename T>
void backwardsPrintDL(DL_list<T>& list) {
    NodeDL<T>* current = list.tail;

    cout << "[";
    while(current)
    {
        cout << current->value;
        if(current->previous)
        {
            cout << " <-> ";
        }
        current = current->previous;
    }
    cout << "]" << endl;
}