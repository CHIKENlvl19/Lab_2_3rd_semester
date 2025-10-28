#pragma once

#include <iostream>
#include <optional>
#include "../Task_7/DL_List.h"
#include "../Task_7/HashTableOA.h"

using namespace std;

enum class Command {
    SET, GET, UNKNOWN
};

Command getCommand(const string& input) {
    if(input == "GET")
    {
        return Command::GET;
    }
    if(input == "SET")
    {
        return Command::SET;
    }

    return Command::UNKNOWN;
}

template <typename T>
struct Pair {
    size_t key;
    T value;

    bool operator==(const Pair& other) const {
        return key == other.key && value == other.value;
    }

    friend ostream& operator<< (ostream& os, const Pair& p) {
        os << "(" << p.key << "," << p.value << ")";
        return os;
    }
};

template <typename T>
class LRUCache {
 public:

    LRUCache(size_t cap) : capacity(cap), size(0) {}

    optional<T> get(size_t key) {
        NodeDL<Pair<T>>* nodePtr = table.find(key);

        if(nodePtr == nullptr)
        {
            return nullopt;
        }

        list.moveNodeToHead(nodePtr);

        return nodePtr->value.value;
    }

    void set(size_t key, const T& value) {
        NodeDL<Pair<T>>* nodePtr = table.find(key);

        if(nodePtr != nullptr)
        {
            nodePtr->value.value = value;
            list.moveNodeToHead(nodePtr);
            return;
        }
        else
        {
            if(size == capacity)
            {
                if(list.tail != nullptr)
                {
                    size_t oldKey = list.tail->value.key;
                    table.remove(oldKey);
                    list.removeNode(list.tail);
                    size--;
                }
            }

            Pair<T> p{key, value};
            list.addHead(p);
            table.insert(key, list.head);
            size++;
        }

    }

    void printCacheState() const {
        NodeDL<Pair<T>>* cur = list.head;
        
        bool first = true;
        while (cur) 
        {
            if (!first)
            {
                cout << ", ";
            }

            cout << cur->value.key << " -> " << cur->value.value;
            first = false;
            cur = cur->next;
        }
        cout << "\n";
    }

 private:

    size_t capacity;
    size_t size;

    DL_list<Pair<T>> list;

    HashTableOA<size_t, NodeDL<Pair<T>>*> table;
};