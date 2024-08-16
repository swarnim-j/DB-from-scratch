// src/common/file_io.h
#ifndef FILE_IO_H
#define FILE_IO_H

#include "hash_table.h"
#include <string>

class FileIO {
public:
    static void save(const HashTable& table, const std::string& filename);
    static void load(HashTable& table, const std::string& filename);

private:
    static std::string getFilePath(const std::string& filename);
};

#endif // FILE_IO_H
