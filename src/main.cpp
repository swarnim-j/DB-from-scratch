// main.cpp
#include <iostream>
#include "database.h"

int main(int argc, char** argv) {
    Database db(45);
    int size = 50;
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = -i;
    }
    for (int i = 0; i < size; i++) {
        db.insert(std::to_string(i), std::to_string(arr[i]));
    }
    std::cout << "Database size: " << db.getNumEntries() << std::endl;
    std::cout << "Table size: " << db.getTableSize() << std::endl;
}