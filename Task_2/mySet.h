#pragma once

#include "../Task_2/hashTable.h"
#include <string>

enum class Command {
    SETADD, SETDEL, SET_AT, SETPRINT, UNKNOWN
};

Command getCommand(const string& cmdStr) {
    if(cmdStr == "SETADD")
    {
        return Command::SETADD;
    }
    if(cmdStr == "SETDEL")
    {
        return Command::SETDEL;
    }
    if(cmdStr == "SET_AT")
    {
        return Command::SET_AT;
    }
    if(cmdStr == "SETPRINT")
    {
        return Command::SETPRINT;
    }

    return Command::UNKNOWN;
}

template<typename T>
class mySet {

 public:
    bool insert(const T& value) {
        return table.insert(value, true);
    }

    bool remove(const T& value) {
        return table.remove(value);
    }

    bool contains(const T& value) const {
        return table.isPresent(value);
    }

    void print() const {
        table.print();
    }

    void loadFromFile(const string& filename = "set.data") {
    ifstream in(filename);
    if(!in.is_open())
    {
        cerr << "Error: cannot open file for reading! (" << filename << ")" << endl;
        return;
    }

    T value;
    while(in >> value)
    {
        table.insert(value, true);
    }

    in.close();
}

    void saveToFile(const string& filename = "set.data") const {
        ofstream out(filename);
        if(!out.is_open())
        {
            cerr << "Error: cannot open file for writing! (" << filename << ")" << endl;
            return;
        }

        for(auto it = table.begin(); it != table.end(); ++it)
        {
            out << *it << "\n";
        }

        out.close();
    }

    size_t size() const {
        return table.getSize();
    }

 private:
    HashTableOA<T, bool> table;
};