#include "HashTableOA.h"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

string randomString(int length) {
    static const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, chars.size() - 1);

    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i)
    {
        s += chars[dist(gen)];
    }
        
    return s;
}

void createRandomTable(int N, HashTableOA<string>& table) {
    for (int i = 0; i < N; ++i) 
    {
        string value = randomString(8);
        table.insert(value);
    }
}

// Замер времени M поисков
int64_t measureSearchTime(HashTableOA<string>& table, int M) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);  // 0 — элемент из таблицы, 1 — случайный

    // Создадим набор ключей для поиска
    vector<string> keys;
    keys.reserve(M);

    for (int i = 0; i < M; ++i) {
        if (dist(gen) == 0 && table.getSize() > 0) {
            // возьмем случайный элемент, который точно есть
            int idx = i % table.getCapacity(); // можно реализовать table.getKeyAt(i)
            keys.push_back("existing" + to_string(idx));
        } else {
            // случайный элемент, которого скорее всего нет
            keys.push_back(randomString(8));
        }
    }

    auto start = high_resolution_clock::now();

    for (const auto& key : keys) 
    {
        table.isPresent(key);
    }

    auto end = high_resolution_clock::now();

    auto result = duration_cast<microseconds>(end - start).count();
    return result;
}

int main() {
    HashTableOA<string> table;

    cout << "Введите количество элементов N: ";
    int N;
    cin >> N;

    cout << "Введите количество поисков M: ";
    int M;
    cin >> M;

    createRandomTable(N, table);

    table.print();
    cout << endl;

    auto searchTime = measureSearchTime(table, M);
    cout << "Время выполнения " << M << " поисков: " << searchTime << " мс." << endl;
    cout << "Среднее время одного поиска: " << (double)searchTime / M << " мс." << endl;

    return 0;
}