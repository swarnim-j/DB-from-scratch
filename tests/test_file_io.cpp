// tests/test_file_io.cpp
#include "file_io.h"
#include "hash_table.h"
#include <cassert>
#include <iostream>
#include <fstream>

// Helper function to compare the contents of two hash tables
bool compareHashTables(const HashTable& table1, const HashTable& table2) {
    auto entries1 = table1.getAllEntries();
    auto entries2 = table2.getAllEntries();
    
    if (entries1.size() != entries2.size()) {
        return false;
    }

    for (const auto& entry : entries1) {
        auto value = table2.find(entry.first);
        if (!value.has_value() || value.value() != entry.second) {
            return false;
        }
    }

    return true;
}

// Test saving and loading functionality
void test_file_io() {
    // Create a hash table and add some entries
    HashTable originalTable(10);
    originalTable.insert("key1", "value1");
    originalTable.insert("key2", "value2");
    originalTable.insert("key3", "value3");

    // Save the table to a file
    const std::string filename = "test_hash_table.dat";
    FileIO::save(originalTable, filename);

    // Create a new hash table and load the data from the file
    HashTable loadedTable(10);
    FileIO::load(loadedTable, filename);

    // Verify that the loaded table matches the original table
    assert(compareHashTables(originalTable, loadedTable));

    // Clean up
    std::remove(filename.c_str());

    std::cout << "FileIO tests passed!" << std::endl;
}

int main() {
    // Run file IO test
    test_file_io();
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}