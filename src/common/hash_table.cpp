// src/common/hash_table.cpp
#include "hash_table.h"
#include <iostream>
#include <optional>
#include <numeric>


HashTable::HashTable(size_t size) : table(size), num_entries(0) {}

size_t HashTable::hash(const std::string& key) const {
    const size_t fnv_prime = 0x811C9DC5;
    size_t hash = 0;
    for (char ch : key) {
        hash ^= ch;
        hash *= fnv_prime;
    }
    return hash % table.size();
}

void HashTable::insert(const std::string& key, const std::string& value) {
    if (loadFactor() > 0.75) {
        resize();
    }
    
    size_t index = hash(key);
    for (auto& kv : table[index]) {
        if (kv.first == key) {
            kv.second = value;
            return;
        }
    }
    table[index].emplace_back(key, value);
    ++num_entries;
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
            --num_entries;
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
    return entries;
}

void HashTable::resize() {
    std::vector<std::vector<std::pair<std::string, std::string>>> new_table(table.size() * 2);

    auto old_table = std::move(table);
    table = std::move(new_table);

    for (const auto& bucket : old_table) {
        for (const auto& kv : bucket) {
            size_t new_index = hash(kv.first) % table.size();
            table[new_index].emplace_back(kv);
        }
    }

    num_entries = std::accumulate(
        table.begin(), 
        table.end(), 
        0, 
        [](size_t acc, const auto& bucket) {
            return acc + bucket.size(); 
        }
    );
}

double HashTable::loadFactor() const {
    return static_cast<double>(num_entries) / table.size();
}