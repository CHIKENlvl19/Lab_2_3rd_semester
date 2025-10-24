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

int theLongestChain() {

}

int theShortestChain() {
    
}

int main() {

    HashTable<mpz_class> table;

    cout << "Введите количество случайных чисел N: ";
    int N;
    cin >> N;

    createRandomTable(N, table);

    table.print();

    return 0;
}