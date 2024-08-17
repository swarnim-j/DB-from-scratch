// src/common/transaction_manager.h
#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <stack>
#include <vector>
#include <string>

class Database;

class TransactionManager {
    private:
    struct Change {
        std::string key;
        std::string oldValue;
        std::string newValue;
    };
    std::stack<std::vector<Change>> transactionStack;

public:
    void beginTransaction();
    void commit();
    void rollback(Database& db);
    void logChange(const std::string& key, const std::string& oldValue, const std::string& newValue);
    bool inTransaction() const;
    const std::vector<Change>& getCurrentTransactionChanges() const;
};

#endif // TRANSACTION_MANAGER_H
