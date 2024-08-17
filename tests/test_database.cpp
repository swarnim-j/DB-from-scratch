// tests/test_database.cpp
#include "database.h"
#include <cassert>
#include <iostream>
#include <thread>

void test_insert_and_find() {
    Database db(10);
    db.insert("key1", "value1");
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for task to execute

    assert(db.find("key1") == "value1");
}

void test_remove() {
    Database db(10);
    db.insert("key1", "value1");
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for task to execute

    db.remove("key1");
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for task to execute

    assert(db.find("key1").empty());
}

void test_transaction_commit() {
    Database db(10);
    db.beginTransaction();
    db.insert("key1", "value1");
    db.insert("key2", "value2");
    db.commit();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for task to execute

    assert(db.find("key1") == "value1");
    assert(db.find("key2") == "value2");
}

void test_transaction_rollback() {
    Database db(10);
    db.insert("key1", "value1");
    db.beginTransaction();
    db.insert("key1", "newValue");
    db.rollback();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for task to execute

    assert(db.find("key1") == "value1");
}

int main() {
    test_insert_and_find();
    test_remove();
    test_transaction_commit();
    test_transaction_rollback();
    std::cout << "Database tests passed!" << std::endl;
    return 0;
}
