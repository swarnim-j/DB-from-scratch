// src/common/database.cpp
#include "database.h"
#include <functional>
#include <stdexcept>

Database::Database(size_t size) : table(size) {}
//Database::Database(size_t size, size_t numThreads) : table(size), threadPool(numThreads) {}

void Database::insert(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(dbMutex);

    std::string oldValue = table.find(key).value_or("");

    if (transactionManager.inTransaction()) {
        transactionManager.logChange(key, oldValue, value);
    }

    table.insert(key, value);
}

std::string Database::find(const std::string& key) {
    std::lock_guard<std::mutex> lock(dbMutex);
    return table.find(key).value_or("");
}

void Database::remove(const std::string& key) {
    std::lock_guard<std::mutex> lock(dbMutex);

    std::string oldValue = table.find(key).value_or("");

    if (transactionManager.inTransaction()) {
        transactionManager.logChange(key, oldValue, "");
    }

    table.remove(key);
}

void Database::beginTransaction() {
    std::lock_guard<std::mutex> lock(dbMutex);
    transactionManager.beginTransaction();
}

void Database::commit() {
    std::lock_guard<std::mutex> lock(dbMutex);
    transactionManager.commit();
}

void Database::rollback() {
    std::lock_guard<std::mutex> lock(dbMutex);
    
    if (transactionManager.inTransaction()) {
        const auto& changes = transactionManager.getCurrentTransactionChanges();
        for (const auto& change : changes) {
            applyChange(change.key, change.oldValue);
        }
        transactionManager.rollback(*this);
    }
}

void Database::applyChange(const std::string& key, const std::string& value) {
    if (value.empty()) {
        table.remove(key);
    } else {
        table.insert(key, value);
    }
}

size_t Database::getNumEntries() {
    std::lock_guard<std::mutex> lock(dbMutex);
    return table.size();
}

size_t Database::getTableSize() {
    std::lock_guard<std::mutex> lock(dbMutex);
    return table.capacity();
}
