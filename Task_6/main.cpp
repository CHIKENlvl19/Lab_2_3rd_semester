#include "HashTable.h"
#include "DL_List.h"

using namespace std;

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

int main() {

    HashTable<mpz_class> table;

    cout << "Введите количество случайных чисел N: ";
    int N;
    cin >> N;

    createRandomTable(N, table);

    table.print();
    cout << endl;

    cout << "Самая длинная цепочка - " << theLongestChain(table) << " символов." << endl;
    cout << "Самая короткая цепочка - " << theShortestChain(table) << " символов." << endl;

    return 0;
}