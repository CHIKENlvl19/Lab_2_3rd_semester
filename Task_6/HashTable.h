#pragma once

#include <iostream>
#include <fstream>
#include <random>
#include <gmpxx.h>
#include "DL_List.h"

using namespace std;



template <typename T>
struct Bucket {
    int hash;
    DL_list<T> values;
};

template <typename T>
class HashTable {

 public:
    int hashing(T value) {
        gmp_randstate_t state;
        gmp_randinit_default(state);
        random_device rd;
        unsigned long seed = rd();
        mpz_class seed_mpz = seed;
        gmp_randseed(state, seed_mpz.get_mpz_t());


        // h(k) = ((a*k + b) mod p) mod m - универсальное хеширование
        mpz_class a, b;
        mpz_class p = generate_safe_prime(state, 64);

        gmp_randclear(state);
        return -1;
    }

 private:
    Bucket* bucket;
    
    float loadFactor;
    int size;
    int capaity;
};