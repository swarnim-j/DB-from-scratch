// src/common/hash_table.cpp
#include "hash_table.h"
#include <iostream>
#include <optional>

HashTable::HashTable(size_t size) : table(size) {}

size_t HashTable::hash(const std::string& key) const {
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
    for (auto& kv : table[index]) {
        if (kv.first == key) {
            kv.second = value;
            return;
        }
    }
    table[index].emplace_back(key, value);
}

std::optional<std::string> HashTable::find(const std::string& key) {
    size_t index = hash(key);
    for (const auto& kv : table[index]) {
        if (kv.first == key) {
            return kv.second;
        }
    }
    return std::nullopt;
}

void HashTable::remove(const std::string& key) {
    size_t index = hash(key);
    auto& bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            return;
        }
    }
}

std::vector<std::pair<std::string, std::string>> HashTable::getAllEntries() const {
    std::vector<std::pair<std::string, std::string>> entries;
    for (const auto& bucket : table) {
        for (const auto& kv : bucket) {
            entries.push_back(kv);
        }
    }
}