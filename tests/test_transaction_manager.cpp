// tests/test_transaction_manager.cpp
#include "transaction_manager.h"
#include "database.h"
#include <cassert>
#include <iostream>

void test_begin_and_commit_transaction() {
    TransactionManager tm;
    tm.beginTransaction();
    assert(tm.inTransaction());

    tm.commit();
    assert(!tm.inTransaction());
}

void test_log_change_and_rollback() {
    TransactionManager tm;
    Database db(100);
    tm.beginTransaction();

    tm.logChange("key1", "oldValue1", "newValue1");
    tm.logChange("key2", "oldValue2", "newValue2");

    const auto& changes = tm.getCurrentTransactionChanges();
    assert(changes.size() == 2);
    assert(changes[0].key == "key1");
    assert(changes[0].oldValue == "oldValue1");
    assert(changes[0].newValue == "newValue1");
    assert(changes[1].key == "key2");
    assert(changes[1].oldValue == "oldValue2");
    assert(changes[1].newValue == "newValue2");

    tm.rollback(db);
    assert(!tm.inTransaction());
}

void test_no_active_transaction_throws() {
    TransactionManager tm;
    try {
        tm.getCurrentTransactionChanges();
        assert(false); // This line should not be reached
    } catch (const std::runtime_error& e) {
        assert(true); // Expected exception
    }
}

int main() {
    test_begin_and_commit_transaction();
    test_log_change_and_rollback();
    test_no_active_transaction_throws();
    std::cout << "TransactionManager tests passed!" << std::endl;
    return 0;
}