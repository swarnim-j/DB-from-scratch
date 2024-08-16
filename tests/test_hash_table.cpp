// tests/test_hash_table.cpp

#include "hash_table.h"
#include <cassert>
#include <iostream>

void test_insert_find() {
    HashTable table(100);
    table.insert("key1", "value1");
    assert(table.find("key1") == "value1");
}

void test_collision_handling() {
    HashTable table(5); // Small size to force collisions
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    assert(table.find("key1") == "value1");
    assert(table.find("key2") == "value2");
}

void test_resize() {
    HashTable table(2);
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.insert("key3", "value3"); // Should trigger resize
    assert(table.find("key1") == "value1");
    assert(table.find("key2") == "value2");
    assert(table.find("key3") == "value3");
}

void test_delete() {
    HashTable table(100);
    table.insert("key1", "value1");
    table.remove("key1");
    assert(!table.find("key1").has_value()); // Now returns std::optional, check if it has no value
}

int main() {
    test_insert_find();
    test_collision_handling();
    test_resize();
    test_delete();
    // Add more tests as needed
    std::cout << "All tests passed!" << std::endl;
    return 0;
}