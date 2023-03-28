#ifndef P4_H
#define P4_H

#include <vector>
#include <string>
#include <map>

enum probingMethods {
    linearProbing = 0,
    quadraticProbing = 1,
    doubleHashing = 2
};

class HashTable {

public:
    HashTable(int tableSize, probingMethods probingMethod, int aValue = 0);

    int totalCollisions;
    int tableSize;
    int aValue;

    probingMethods probingMethod;

    uint64_t djb2Hash(std::string str);
    int indexEmpty(uint64_t hash, std::string str);
    int mapSize();
    void searchMap(std::string str);
    void insert(std::string str);
    void search(std::string);
    void insertToMap(std::string str, int lineNum);
    void projectPrint(int numOfWords, std::string str);
    void print();


private:
    std::vector<std::string> tableStructure;
    std::map<std::string,std::vector<int>> mapStructure;

};

#endif //P4_H
