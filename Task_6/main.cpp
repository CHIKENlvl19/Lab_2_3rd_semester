#include "HashTable.h"
#include "DL_List.h"

using namespace std;

int main() {

    HashTable<string> table;

    table.insert("apple");
    table.insert("banana");
    table.insert("cherry");
    table.insert("shit");
    table.insert("kek");
    table.insert("pipiska");

    table.print();

    cout << "Has 'banana'? " << (table.isPresent("banana") ? "yes" : "no") << endl;

    table.remove("banana");

    table.print();

    return 0;
}