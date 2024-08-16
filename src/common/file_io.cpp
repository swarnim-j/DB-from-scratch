// src/common/file_io.cpp
#include "file_io.h"
#include <fstream>
#include <stdexcept>

void FileIO::save(const HashTable& table, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        throw std::runtime_error("Could not open file for writing.");
    }

    // Iterate over the hash table and write each key-value pair to the file
    for (const auto& pair : table.getAllEntries()) {
        const std::string& key = pair.first;
        const std::string& value = pair.second;

        // Write the length of the key
        uint32_t key_length = key.size();
        ofs.write(reinterpret_cast<const char*>(&key_length), sizeof(key_length));

        // Write the key itself
        ofs.write(key.data(), key_length);

        // Write the length of the value
        uint32_t value_length = value.size();
        ofs.write(reinterpret_cast<const char*>(&value_length), sizeof(value_length));

        // Write the value itself
        ofs.write(value.data(), value_length);
    }

    ofs.close();
}

void FileIO::load(HashTable& table, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        throw std::runtime_error("Could not open file for reading.");
    }

    while (ifs) {
        uint32_t key_length = 0, value_length = 0;

        // Read the length of the key
        ifs.read(reinterpret_cast<char*>(&key_length), sizeof(key_length));
        if (ifs.eof()) break;

        // Read the key itself
        std::string key(key_length, '\0');
        ifs.read(&key[0], key_length);

        // Read the length of the value
        ifs.read(reinterpret_cast<char*>(&value_length), sizeof(value_length));

        // Read the value itself
        std::string value(value_length, '\0');
        ifs.read(&value[0], value_length);

        // Insert the key-value pair into the hash table
        table.insert(key, value);
    }

    ifs.close();
}

