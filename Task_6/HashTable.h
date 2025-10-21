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
        mpz_class Hash;
        mpz_class a;
        mpz_urandomb(a.get_mpz_t(), state, 64);
        mpz_class b;
        mpz_urandomb(b.get_mpz_t(), state, 64);
        mpz_class p = generate_safe_prime(state, 64);

        Hash = ((a * (mzp_class)value + b) % p) % capaity;

        gmp_randclear(state);
        return Hash;
    }

 private:
    Bucket* bucket;
    
    float loadFactor;
    int size;
    int capaity;
};