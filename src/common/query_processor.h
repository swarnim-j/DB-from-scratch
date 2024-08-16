// src/common/query_processor.h
#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include "hash_table.h"
#include <string>

class QueryProcessor {
public:
    QueryProcessor(HashTable& db);
    void processQuery(const std::string& query);

private:
    HashTable& database;
};

#endif // QUERY_PROCESSOR_H