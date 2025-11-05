#pragma once

#include "hashTableOA.h"

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

    size_t size() const {
        return table.getSize();
    }

    void print() const {
        table.print();
    }

    mySet<T> unionWith(const mySet<T>& other) const {
        mySet<T> result = *this; // копируем текущее множество
        
        for (auto it = other.table.begin(); it != other.table.end(); ++it) 
        { // итерируемся по второму
            result.insert(*it); // добавляем (если уже есть — ничего не произойдёт)
        }
        
        return result;
    }

    mySet<T> intersectWith(const mySet<T>& other) const {
        mySet<T> result;
        
        for (auto it = this->table.begin(); it != this->table.end(); ++it) 
        {
            if (other.contains(*it))
            {
                result.insert(*it);
            } 
        }
        
        return result;
    }

    mySet<T> differenceWith(const mySet<T>& other) const {
        mySet<T> result;
        for (auto it = this->table.begin(); it != this->table.end(); ++it) 
        {
            if (!other.contains(*it))
            {
                result.insert(*it);
            }
        }
        
        return result;
    }

 private:
    HashTableOA<T, bool> table;
};