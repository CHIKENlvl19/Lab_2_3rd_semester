#include "HashTableOA.h"

using namespace std;

int main() {

    HashTableOA<string> table;

    table.insert("куку");
    table.insert("я");

    table.remove("я");

    table.print();

    if(table.isPresent("куку"))
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }

    return 0;
}