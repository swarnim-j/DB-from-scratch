// src/common/transaction_manager.cpp
#include "transaction_manager.h"
#include "database.h"

void TransactionManager::beginTransaction() {
    transactionStack.push({});
}

void TransactionManager::commit() {
    if (!transactionStack.empty()) {
        transactionStack.pop();
    }
}

void TransactionManager::rollback(Database& db) {
    if (!transactionStack.empty()) {
        const auto& changes = transactionStack.top();
        for (const auto& change : changes) {
            // Rollback: Apply the old value to the database (handled by the database class)
            db.applyChange(change.key, change.oldValue);
        }
        transactionStack.pop();
    }
}

void TransactionManager::logChange(const std::string& key, const std::string& oldValue, const std::string& newValue) {
    if (!transactionStack.empty()) {
        transactionStack.top().push_back({key, oldValue, newValue});
    }
}

bool TransactionManager::inTransaction() const {
    return !transactionStack.empty();
}

const std::vector<TransactionManager::Change>& TransactionManager::getCurrentTransactionChanges() const {
    if (!transactionStack.empty()) {
        return transactionStack.top();
    }
    throw std::runtime_error("No active transaction");
}
