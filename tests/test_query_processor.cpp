// tests/test_query_processor.cpp
#include "query_processor.h"
#include "hash_table.h"
#include <cassert>
#include <iostream>
#include <sstream>

// Helper function to capture standard output
std::string capture_stdout(std::function<void()> func) {
    std::ostringstream oss;
    std::streambuf* orig_buf = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(orig_buf);
    return oss.str();
}

void test_query_processor_insert() {
    HashTable table(10);
    QueryProcessor qp(table);

    qp.processQuery("INSERT key1 value1");
    assert(table.find("key1") == "value1");

    qp.processQuery("INSERT key2 value2");
    assert(table.find("key2") == "value2");
}

void test_query_processor_find() {
    HashTable table(10);
    QueryProcessor qp(table);

    qp.processQuery("INSERT key1 value1");
    std::string output = capture_stdout([&qp]() {
        qp.processQuery("FIND key1");
    });
    assert(output == "Found: key1 -> value1\n");

    output = capture_stdout([&qp]() {
        qp.processQuery("FIND key2");
    });
    assert(output == "Key not found: key2\n");
}

void test_query_processor_delete() {
    HashTable table(10);
    QueryProcessor qp(table);

    qp.processQuery("INSERT key1 value1");
    qp.processQuery("DELETE key1");
    
    std::string output = capture_stdout([&qp]() {
        qp.processQuery("FIND key1");
    });
    assert(output == "Key not found: key1\n");
}

int main() {
    test_query_processor_insert();
    test_query_processor_find();
    test_query_processor_delete();
    
    std::cout << "All QueryProcessor tests passed!" << std::endl;
    return 0;
}