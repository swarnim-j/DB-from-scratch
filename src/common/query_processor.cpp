// src/common/query_processor.cpp
#include "query_processor.h"
#include <sstream>
#include <iostream>

// Constructor
QueryProcessor::QueryProcessor(HashTable& db) : database(db) {}

// Process the query
void QueryProcessor::processQuery(const std::string& query) {
    std::istringstream iss(query);
    std::string command, key, value;

    iss >> command >> key;
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    if (command == "INSERT") {
        iss >> value;
        database.insert(key, value);
        std::cout << "Inserted: " << key << " -> " << value << std::endl;
    } else if (command == "FIND") {
        auto result = database.find(key);
        if (result) {
            std::cout << "Found: " << key << " -> " << *result << std::endl;
        } else {
            std::cout << "Key not found: " << key << std::endl;
        }
    } else if (command == "DELETE") {
        database.remove(key);
        std::cout << "Deleted key: " << key << std::endl;
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}