// src/common/query_processor.cpp
#include "query_processor.h"
#include <sstream>
#include <iostream>

// Constructor
QueryProcessor::QueryProcessor(HashTable& db) : database(db) {}

// Process the query
void QueryProcessor::processQuery(const std::string& query) {
    std::istringstream iss(query);
    std::string command;
    std::string key, value;

    iss >> command >> key;
    if (command == "INSERT") {
        iss >> value;
        database.insert(key, value);
    } else if (command == "FIND") {
        std::cout << database.find(key) << std::endl;
    } else if (command == "DELETE") {
        database.remove(key);
    }
}