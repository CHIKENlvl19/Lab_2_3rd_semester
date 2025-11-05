#pragma once

#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

using namespace std;


template <typename Key, typename Value>
class HashTableOA {
 public:

    struct Iterator {
        const HashTableOA* table;
        size_t index;

        Iterator(const HashTableOA* t, size_t i) : table(t), index(i) {}

        const Key& operator*() const {
            return table->table[index].key;
        }

        Iterator& operator++() {
            index++;
            advanceToNext();
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index || table != other.table;
        }

        void advanceToNext() {
            while(index < table->capacity && 
                (!table->table[index].isOccupied || table->table[index].isDeleted)) {
                    index++;
            }
        }
    };

    Iterator begin() const {
        Iterator it(this, 0);
        it.advanceToNext();
        return it;
    }

    Iterator end() const {
        return Iterator(this, capacity);
    }


    HashTableOA(size_t capacity = 16)
        : size(0), capacity(capacity), loadFactor(0.0f)
    {
        table = new Cell[capacity];
        init();
    }

    HashTableOA(const HashTableOA& other)
        : size(other.size), capacity(other.capacity), loadFactor(other.loadFactor)
    {
        table = new Cell[capacity];
        init();

        for(size_t i = 0; i < capacity; i++)
        {
            if (other.table[i].isOccupied && !other.table[i].isDeleted) 
            {
                insert(other.table[i].key, other.table[i].value);
            }
        }
    }

    void clean() {
        delete[] table;
    }

    ~HashTableOA() {
        clean();
    }

    size_t getSize() const {
        return size;
    }

    float getLoadFactor() const {
        return static_cast<float>(size) / capacity;
    }

    bool insert(const Key& key, const Value& value) {
        
        if(isPresent(key))
        {
            return false;
        }
        
        size_t index;
        
        for(size_t i = 0; i < capacity; i++)
        {
            index = (h1(key) + i * h2(key)) % capacity;

            if(!table[index].isOccupied || table[index].isDeleted)
            {
                table[index].key = key;
                table[index].value = value;
                table[index].isOccupied = true;
                table[index].isDeleted = false;
                size++;
                loadFactor = getLoadFactor();
                return true;
            }
        }

        cerr << "Error: table is full!" << endl;
        return false;
    }

    bool isPresent(const Key& key) const {
        size_t index;

        for(size_t i = 0; i < capacity; i++)
        {
            index = (h1(key) + i * h2(key)) % capacity;

            if(!table[index].isOccupied && !table[index].isDeleted)
            {
                return false;
            }

            if(table[index].isOccupied && table[index].key == key)
            {
                return true;
            }
        }

        return false;
    }

    Value find (const Key& key) {
        size_t index;

        for(size_t i = 0; i < capacity; i++)
        {
            index = (h1(key) + i * h2(key)) % capacity;

            if(!table[index].isOccupied && !table[index].isDeleted)
            {
                return Value();
            }

            if(table[index].isOccupied && table[index].key == key)
            {
                return table[index].value;
            }
        }

        return Value();
    }

    bool remove(const Key& key) {
        size_t index;

        for(size_t i = 0; i < capacity; i++)
        {
            index = (h1(key) + i * h2(key)) % capacity;

            if(!table[index].isOccupied && !table[index].isDeleted)
            {
                return false;
            }

            if(table[index].isOccupied && table[index].key == key)
            {
                table[index].isDeleted = true;
                table[index].isOccupied = false;
                size--;
                loadFactor = getLoadFactor();
                return true;
            }
        }

        return false;
    }

    void print() const {
        for (size_t i = 0; i < capacity; i++) {
            if (table[i].isOccupied && !table[i].isDeleted)
            {
                cout << "[" << i << "]" << table[i].value << endl;
            }
        }
    }

 private:
    struct Cell {
        Key key;
        Value value;
        bool isOccupied;
        bool isDeleted;

        Cell() : isOccupied(false), isDeleted(false) {}
    };

    Cell* table;
    size_t size;
    size_t capacity;
    float loadFactor;

    int a, b;
    int p = 1000000007;

    void init() {

        mt19937 gen(1337);
        uniform_int_distribution<int> dist(1, 1000);

        a = dist(gen);
        b = dist(gen);
    }


    size_t h1(const Key& key) const {
        long long keyValue = 0;

        if constexpr (is_integral_v<Key> || is_floating_point_v<Key>)
        {
            keyValue = static_cast<long long>(key);
        }
        else
        {
            unsigned long long hash = 0;
            for(char c : key)
            {
                hash = hash * 131 + static_cast<unsigned char>(c);
            }

            keyValue = hash;
        }

        return static_cast<size_t>(( (a * keyValue + b) % p ) % capacity);
    }

    size_t h2(const Key& key) const {
        const double A = 0.6180339887;
        double k_double = 0.0;

        if constexpr (is_integral_v<Key> || is_floating_point_v<Key>)
        {
            k_double = static_cast<double>(key);
        }
        else
        {
            unsigned long long hashValue = 0;

            for(char c : key)
            {
                hashValue = hashValue * 131 + static_cast<unsigned char>(c);
            }

            k_double = static_cast<double>(hashValue);
        }

        double frac = k_double * A - floor(k_double * A);
        return static_cast<size_t>(capacity * frac) + 1;
    }
};