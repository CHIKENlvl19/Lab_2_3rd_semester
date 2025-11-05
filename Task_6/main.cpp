#include "HashTable.h"
#include "DL_List.h"
#include <chrono>
#include <string>
#include <random>

using namespace std;
using namespace std::chrono;

string randomString(int len) {
    static const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(0, alphabet.size() - 1);

    string result;
    result.reserve(len);
    for (int i = 0; i < len; i++)
    {
        result += alphabet[dist(gen)];
    }
    return result;
}

void createRandomTable(int N, HashTable<mpz_class, string>& table) {
    random_device rd;
    unsigned long seed = rd();
    mpz_class seed_mpz = seed;

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed(state, seed_mpz.get_mpz_t());

    for (int i = 0; i < N; i++)
    {
        mpz_class key;
        mpz_urandomb(key.get_mpz_t(), state, 64);
        string value = randomString(8);
        table.insert(key, value);
    }

    gmp_randclear(state);
}

int theLongestChain(const HashTable<mpz_class, string>& table) {
    int maxChainLength = 0;

    for (int i = 0; i < table.capacity; i++)
    {
        int chainLength = table.buckets[i].values.size;
        if (chainLength > maxChainLength)
        {
            maxChainLength = chainLength;
        }
    }
    return maxChainLength;
}

int theShortestChain(HashTable<mpz_class, string>& table) {
    int minChainLength = 99999;

    for (int i = 0; i < table.capacity; i++)
    {
        int chainLength = table.buckets[i].values.size;
        if (chainLength < minChainLength)
        {
            minChainLength = chainLength;
        }
    }
    return minChainLength;
}

double measureSearchTime(HashTable<mpz_class, string>& table, int M) {
    random_device rd;
    unsigned long seed = rd();
    mpz_class seed_mpz = seed;

    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed(state, seed_mpz.get_mpz_t());

    auto start = high_resolution_clock::now();

    for (int i = 0; i < M; i++)
    {
        mpz_class key;
        mpz_urandomb(key.get_mpz_t(), state, 64);
        table.isPresent(key);
    }

    auto end = high_resolution_clock::now();
    gmp_randclear(state);

    double result = duration_cast<microseconds>(end - start).count() / 1000.0;
    return result;
}


void testOperations() {
    cout << "\nПроверка основных операций" << endl;

    HashTable<mpz_class, string> testTable;

    mpz_class key1 = 12345;
    mpz_class key2 = 67890;

    cout << "Добавляем (12345, 'alpha') и (67890, 'beta')" << endl;
    testTable.insert(key1, "alpha");
    testTable.insert(key2, "beta");

    cout << "Поиск ключа 12345: " << (testTable.isPresent(key1) ? "найден" : "не найден") << endl;
    cout << "Значение по ключу 67890: " << testTable.find(key2) << endl;

    cout << "Удаляем ключ 12345..." << endl;
    testTable.remove(key1);
    cout << "Повторный поиск ключа 12345: " << (testTable.isPresent(key1) ? "не найден" : "не найден") << endl;

    testTable.clean();
    cout << "Таблица очищена. Размер = 0" << endl;
}

int main() {

    HashTable<mpz_class, string> table;

    cout << "Введите количество элементов N: ";
    int N;
    cin >> N;

    createRandomTable(N, table);

    cout << "Введите количество поисков M: ";
    int M;
    cin >> M;

    cout << "\nСодержимое таблицы:" << endl;
    table.print();
    cout << endl;

    cout << "Самая длинная цепочка — " << theLongestChain(table) << " элементов." << endl;
    cout << "Самая короткая цепочка — " << theShortestChain(table) << " элементов." << endl;

    double searchTime = measureSearchTime(table, M);
    cout << "\nВремя выполнения " << M << " поисков: " << searchTime << " мс." << endl;
    cout << "Среднее время одного поиска: " << (searchTime / M) << " мс." << endl;

    
    cout << "\nОчистка таблицы..." << endl;
    table.clean();
    cout << "Работа завершена. Таблица очищена." << endl;

    testOperations();

    return 0;
}