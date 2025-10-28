#pragma once

#include "../Task_2/hashTable.h"

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
        return table.insert(value);
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
        table.loadFromFile(filename);
    }

    void saveToFile(const string& filename = "set.data") {
        table.saveToFile(filename);
    }

    size_t size() const {
        return table.getSize();
    }

 private:
    HashTableOA<T> table;
};