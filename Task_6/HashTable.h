#pragma once

#include <iostream>
#include <fstream>
#include <random>
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

    HashTable() : loadFactor(0.0), size(0), capacity(5) {
        
        buckets = new Bucket<T>[capacity];

        gmp_randinit_default(state);
        random_device rd;
        unsigned long seed = rd();
        mpz_class seed_mpz = seed;
        gmp_randseed(state, seed_mpz.get_mpz_t());

        a = get_random_64();
        b = get_random_64();
        p = generate_safe_prime(state, 64);
    }

    ~HashTable() {
        clean();
        gmp_randclear(state);
    }

    int hashing(T value) {
        
    }

    void insert(T value) {

    }

    void remove(T value) {

    }

    bool isPresent(T value) {

    }

    void clean() {

        
    }

 private:
    Bucket<T>* bucket;
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

    mpz_class convertToNumber(const T& value) const {
        if constexpr (is_integral_v<T>) {
            return mpz_class(value);
        }
        else {
            unsigned long long hash = 0;
            for(char c : value) {
                hash = hash * 131 + static_cast<unsigned char>(c);
            }

            return mpz_class(hash);
        }
    }
};