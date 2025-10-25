#pragma once

#include <iostream>
#include <fstream>
#include <random>
#include <fstream>
#include <gmpxx.h>
#include "DL_List.h"

using namespace std;

mpz_class generate_safe_prime(gmp_randstate_t state, int bits) {
    mpz_class prime;
    mpz_urandomb(prime.get_mpz_t(), state, bits);
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
    return prime;
}

template <typename T>
struct Bucket {
    DL_list<T> values;
};

template <typename T>
class HashTable {

 public:

    HashTable() 
        : buckets(nullptr), loadFactor(0.0), size(0), capacity(5) 
    {
        init();    
    }

    explicit HashTable(int cap)
        : buckets(nullptr), loadFactor(0.0), size(0), capacity(cap/100) 
    {
        if(capacity <= 0)
        {
            capacity = 5;
        }
        init();
    }

    ~HashTable() {
        clean();
        gmp_randclear(state);
    }

    int hashing(const T& value) const {
        mpz_class key = /*convertToNumber*/value;
        mpz_class hash = ( (a * key + b) % p ) % capacity;

        return static_cast<int>(hash.get_ui());
    }

    void insert(const T& value) {
        int index = hashing(value);
        if(buckets[index].values.searchByValue(value) == -1)
        {
            buckets[index].values.addTail(value);
            size++;
            loadFactor = static_cast<float>(size) / capacity;
        }
        else
        {
            cerr << "Error, element " << value << " is already in the table!" << endl;
            return;
        }
    }

    void remove(T value) {
        int index = hashing(value);

        if(buckets[index].values.searchByValue(value) == -1)
        {
            cerr << "Error, element " << value << " is not present in talbe!" << endl;
            return;
        }
        else
        {
            buckets[index].values.removeByValue(value);
            size--;
            loadFactor = static_cast<float>(size) / capacity;
        }
    }

    bool isPresent(T value) {
        int index = hashing(value);
        return buckets[index].values.searchByValue(value) != -1;
    }

    void clean() {
        if(buckets)
        {
            delete[] buckets;
            buckets = nullptr;
        }
        size = 0;
        loadFactor = 0.0;
    }

    void print() {
        
        ofstream out;
        out.open("hash_table.txt");
        
        for(int i = 0; i < capacity; i++)
        {
            cout << "[" << i << "]: ";
            buckets[i].values.print();

            out << "[" << i << "]: ";
            buckets[i].values.print(out);
        }
        out.close();
    }

 private:
    Bucket<T>* buckets;
    float loadFactor;
    size_t size;
    int capacity;


    mpz_class a, b, p;
    gmp_randstate_t state;

    mpz_class get_random_64() {
        mpz_class r;
        mpz_urandomb(r.get_mpz_t(), state, 64);
        return r;
    }

    void init() {
        buckets = new Bucket<T>[capacity];

        gmp_randinit_default(state);
        random_device rd;
        unsigned long seed = 1488;
        mpz_class seed_mpz = seed;
        gmp_randseed(state, seed_mpz.get_mpz_t());

        a = get_random_64();
        b = get_random_64();
        p = generate_safe_prime(state, 64);
    }

    friend int theLongestChain(const HashTable<mpz_class>& table);
    friend int theShortestChain(HashTable<mpz_class>& table);

    /*mpz_class convertToNumber(const T& value) const {
        if constexpr (is_integral_v<T>) {
            return mpz_class(value);
        }
        else {
            unsigned long long hash = 0;
            for(char c : value) {
                hash = hash * 131 + static_cast<unsigned char>(c);
            }

            return mpz_class(static_cast<unsigned long>(hash));
        }
    }*/
};