// src/common/hash_table.cpp
#include "hash_table.h"
#include <iostream>

HashTable::HashTable(size_t size) : table(size) {}

size_t HashTable::hash(const std::string& key) {
    // Simple hash function
    size_t hash = 0;
    for (char ch : key) {
        // TODO: change hash function to something better
        hash = (hash * 31) + ch;
    }
    return hash % table.size();
}

void HashTable::insert(const std::string& key, const std::string& value) {
    size_t index = hash(key);
    table[index] = {key, value};
}

std::string HashTable::find(const std::string& key) {
    size_t index = hash(key);
    return table[index].second;
}

void HashTable::remove(const std::string& key) {
    size_t index = hash(key);
    table[index] = {"", ""};
}