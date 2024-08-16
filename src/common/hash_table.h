// src/common/hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>

class HashTable {
public:
    HashTable(size_t size);
    void insert(const std::string& key, const std::string& value);
    std::string find(const std::string& key);
    void remove(const std::string& key);

private:
    std::vector<std::pair<std::string, std::string>> table;
    size_t hash(const std::string& key);
};

#endif // HASH_TABLE_H