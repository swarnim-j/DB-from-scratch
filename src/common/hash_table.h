// src/common/hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <optional>

class HashTable {
public:
    HashTable(size_t size);
    void insert(const std::string& key, const std::string& value);
    std::optional<std::string> find(const std::string& key);
    void remove(const std::string& key);
    std::vector<std::pair<std::string, std::string>> getAllEntries() const;

private:
    std::vector<std::vector<std::pair<std::string, std::string>>> table;
    size_t num_entries;
    size_t hash(const std::string& key) const;
    void resize();
    double loadFactor() const;
};

#endif // HASH_TABLE_H