#include <iostream>
#include <sstream>
#include "LRU_Cache.h"

using namespace std;

int main() {
    size_t cacheSize;

    while (true) 
    {
        cout << "Введите размер кэша: ";
        cin >> cacheSize;

        if (cacheSize < 2)
        {
            cout << "Размер кэша должен быть больше единицы! Попробуйте ещё раз.\n";
        } 
        else 
        {
            break;
        }
    }

    LRUCache<int> cache(cacheSize);
    cout << "Cache Size = " << cacheSize << "\n";

    cout << "Введите команды (SET x y / GET x). Чтобы завершить — напишите EXIT.\n";

    string input;
    vector<int> getResults;

    while (true) 
    {
        cout << "> ";
        cin >> input;
        Command cmd = getCommand(input);

        if (cmd == Command::SET) 
        {
            size_t key;
            int value;
            cin >> key >> value;
            
            cache.set(key, value);
            cout << "SET " << key << " " << value << " : ";
            cache.printCacheState();
        } 
        else if (cmd == Command::GET) 
        {
            size_t key;
            cin >> key;
            auto result = cache.get(key);
            
            if (result.has_value()) {
                cout << "GET " << key << " : " << *result << "\n";
                getResults.push_back(*result);
            } else {
                cout << "GET " << key << " : -1\n";
                getResults.push_back(-1);
            }
        }
        else if (input == "EXIT") 
        {
            break;
        } 
        else {
            cout << "Неизвестная команда! Используйте SET / GET / EXIT.\n";
        }
    }

    cout << "\nРезультаты GET-запросов: ";
    for (size_t i = 0; i < getResults.size(); ++i)
    {
        if (i)
        {
            cout << ' ';
        }
        cout << getResults[i];
    }
    cout << "\n";

    return 0;
}
