// src/common/database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "thread_pool.h"
#include "transaction_manager.h"
#include "hash_table.h"
#include <string>
#include <vector>
#include <mutex>

class Database {
public:
    // Database(size_t size, size_t numThreads);
    Database(size_t size);
    void insert(const std::string& key, const std::string& value);
    std::string find(const std::string& key);
    void remove(const std::string& key);
    void beginTransaction();
    void commit();
    void rollback();
    void applyChange(const std::string& key, const std::string& value);
    size_t getNumEntries();
    size_t getTableSize();

private:
    HashTable table;
    TransactionManager transactionManager;
    // ThreadPool threadPool;
    std::mutex dbMutex;
};

#endif // DATABASE_H