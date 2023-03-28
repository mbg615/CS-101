#include <iostream>
#include <algorithm>
#include <string>

#include "p4.h"

HashTable::HashTable(int tableSize, probingMethods probingMethod, int aValue) {
    this->tableSize = tableSize;
    this->probingMethod = probingMethod;
    this->aValue = aValue;
    totalCollisions = 0;

    tableStructure.clear();
    tableStructure.resize(tableSize);
    std::fill(tableStructure.begin(), tableStructure.end(), "\0");
}

uint64_t HashTable::djb2Hash(std::string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

int HashTable::mapEmpty(uint64_t hash, std::string str) {
    int index;
    int j;
    switch(probingMethod) {
        case linearProbing:
            j = 0;
            do {
                index = (hash + j) % tableSize;
                this->totalCollisions++;
                j++;
                if(tableStructure[index] == str) break;
            } while(tableStructure[index] != "\0");
            this->totalCollisions--;
            break;

        case quadraticProbing:
            j = 0;
            do {
                index = (hash + (j * j)) % tableSize;
                this->totalCollisions++;
                j++;
                if(tableStructure[index] == str) break;
            } while(tableStructure[index] != "\0");
            this->totalCollisions--;
            break;

        case doubleHashing:
            j = 0;
            do {
                index = (hash + (j * (aValue - (hash % aValue)))) % tableSize;
                this->totalCollisions++;
                j++;
                if(tableStructure[index] == str) break;
            } while(tableStructure[index] != "\0");
            this->totalCollisions--;
            break;
        default:
            std::cerr << "Error: No Probing method defined, doing nothing.\n";
    }
    return index;
}

void HashTable::insert(std::string str) {
    int index;
    uint64_t hash = djb2Hash(str);
    index = mapEmpty(hash, str);
    tableStructure.at(index) = str;
}

void HashTable::insertToMap(std::string str, int lineNum) {
    if(auto search = mapStructure.find(str); search != mapStructure.end()) {
        if(search->second.back() != lineNum) {
            search->second.push_back(lineNum);
        }
    } else {
        std::vector<int> lineNums;
        lineNums.push_back(lineNum);
        mapStructure.insert(std::pair<std::string, std::vector<int>>(str, lineNums));
    }
}

void HashTable::print() {
    for(int i = 0; i < tableSize; i++) {
        if(i < 10) {
            std::cout << "0" << i << ": " << tableStructure.at(i) << "\n";
        } else {
            std::cout << i << ": " << tableStructure.at(i) << "\n";
        }
    }
    std::cout << "\n";
    for(auto const &element: mapStructure) {
        std::cout << "{" << element.first << ": ";
        for(int i = 0; i < element.second.size(); i++) {
            if(i + 1 == element.second.size()) {
                std::cout << element.second.at(i);
            } else {
                std::cout << element.second.at(i) << ", ";
            }
        }
        std::cout << "}\n";
    }
}