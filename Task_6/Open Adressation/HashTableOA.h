#pragma once

#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

using namespace std;


template <typename T>
class HashTableOA {
 public:
    HashTableOA(int capacity = 16)
        : size(0), capacity(capacity), loadFactor(0.0f)
    {
        table = new Cell[capacity];
        init();
    }

    ~HashTableOA() {
        delete[] table;
    }

    size_t getSize() const {
        return size;
    }

    float getLoadFactor() const {
        return static_cast<float>(size) / capacity;
    }


    // h(k) = ((a*k + b) mod p) mod m
    size_t h1(const T& key) const {
        long long keyValue;

        if constexpr (is_integral_v<T> || is_floating_point_v<T>)
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

    size_t h2(const T& key) const {
        const double A = 0.6180339887;
        double k_double = 0.0;

        if constexpr (is_integral_v<T> || is_floating_point_v<T>)
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

    void insert(const T& key) {
        size_t index;

        for(size_t i = 0; i < capacity; i++)
        {
            index = (h1(key) + i * h2(key)) % capacity;

            if( (!table[index].isOccupied || table[index].isDeleted) && table[index].value != key)
            {
                table[index].value = key;
                table[index].isOccupied = true;
                table[index].isDeleted = false;
                size++;
                loadFactor = getLoadFactor();
                return;
            }
        }

        cerr << "Error: table is full!" << endl;
    }

    bool isPresent(const T& key) const {
        size_t index;

        for(size_t i = 0; i < capacity; i++)
        {
            index = (h1(key) + i * h2(key)) % capacity;

            if(!table[index].isOccupied && !table[index].isDeleted)
            {
                return false;
            }

            if(table[index].isOccupied && table[index].value == key)
            {
                return true;
            }
        }

        return false;
    }

    void remove(const T& key) {
        size_t index;

        for(size_t i = 0; i < capacity; i++)
        {
            index = (h1(key) + i * h2(key)) % capacity;

            if(!table[index].isOccupied && !table[index].isDeleted)
            {
                return;
            }

            if(table[index].isOccupied && table[index].value == key)
            {
                table[index].isDeleted = true;
                table[index].isOccupied = false;
                size--;
                loadFactor = getLoadFactor();
                return;
            }
        }
    }

    void print() const {
        for(size_t i = 0; i < capacity; i++)
        {
            cout << "[" << i << "]";
            if(table[i].isOccupied)
            {
                cout << table[i].value;
            }
            else if(table[i].isDeleted)
            {
                cout << "(deleted)";
            }
            cout << endl;
        }
    }

 private:
    struct Cell {
        T value;
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

};