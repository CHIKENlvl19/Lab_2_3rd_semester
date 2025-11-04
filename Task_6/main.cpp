#include "HashTable.h"
#include "DL_List.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void createRandomTable(int N, HashTable<mpz_class>& table) {
    random_device rd;
    unsigned long seed = rd();
    mpz_class seed_mpz = seed;

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed(state, seed_mpz.get_mpz_t());

    for(int i = 0; i < N; i++)
    {
        mpz_class number;
        mpz_urandomb(number.get_mpz_t(), state, 64);
        table.insert(number);
    }

    gmp_randclear(state);
}

int theLongestChain(const HashTable<mpz_class>& table) {
    
    int chainLength = 0;
    int maxChainLength = 0;

    for(int i = 0; i < table.capacity; i++)
    {
        chainLength = table.buckets[i].values.size;
        if(chainLength > maxChainLength)
        {
            maxChainLength = chainLength;
        }
    }

    return maxChainLength;
}

int theShortestChain(HashTable<mpz_class>& table) {
    int chainLength = 0;
    int minChainLength = 99999;

    for(int i = 0; i < table.capacity; i++)
    {
        chainLength = table.buckets[i].values.size;
        if(chainLength < minChainLength)
        {
            minChainLength = chainLength;
        }
    }

    return minChainLength;
}

double measureSearchTime(HashTable<mpz_class>& table, int M) {
    random_device rd;
    unsigned long seed = rd();
    mpz_class seed_mpz = seed;

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed(state, seed_mpz.get_mpz_t());

    auto start = high_resolution_clock::now();

    for(int i = 0; i < M; i++)
    {
        mpz_class number;
        mpz_urandomb(number.get_mpz_t(), state, 64);
        table.isPresent(number);
    }

    auto end = high_resolution_clock::now();
    gmp_randclear(state);

    double result = duration_cast<microseconds>(end - start).count() / 1000.0;
    return result;
}

int main() {

    HashTable<mpz_class> table;

    cout << "Введите количество случайных чисел N: ";
    int N;
    cin >> N;

    createRandomTable(N, table);

    cout << "Введите количество поисков М: ";
    int M;
    cin >> M;

    table.print();
    cout << endl;

    cout << "Самая длинная цепочка - " << theLongestChain(table) << " символов." << endl;
    cout << "Самая короткая цепочка - " << theShortestChain(table) << " символов." << endl;

    double searchTime = measureSearchTime(table, M);
    cout << "Время выполнения: " << M << " поисков: " << searchTime << " мс." << endl;
    cout << "Среднее время одного поиска: " << (searchTime / M) << " мс." << endl;

    return 0;
}