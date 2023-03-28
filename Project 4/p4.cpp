#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <fstream>

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

int HashTable::indexEmpty(uint64_t hash, std::string str) {
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

int HashTable::mapSize() {
    return mapStructure.size();
}

void HashTable::searchMap(std::string str) {
    if(auto search = mapStructure.find(str); search != mapStructure.end()) {
        std::cout << str << " appears on lines [";
        for(int i = 0; i < search->second.size(); i++) {
            if(i + 1 == search->second.size()) {
                std::cout << search->second.at(i) << "]\n";
            } else {
                std::cout << search->second.at(i) << ",";
            }
        }
    } else {
        std::cout << str << " appears on lines []\n";
    }
}

void HashTable::insert(std::string str) {
    int index;
    uint64_t hash = djb2Hash(str);
    index = indexEmpty(hash, str);
    tableStructure.at(index) = str;
}

void HashTable::search(std::string str) {
    uint64_t hash = djb2Hash(str);
    int collisionCount = 0;
    int index;
    int j;
    switch(probingMethod) {
        case linearProbing:
            j = 0;
            do {
                index = (hash + j) % tableSize;
                collisionCount++;
                j++;
                if(tableStructure[index] == str) break;
            } while(tableStructure[index] != "\0");
            collisionCount--;
            break;

        case quadraticProbing:
            j = 0;
            do {
                index = (hash + (j * j)) % tableSize;
                collisionCount++;
                j++;
                if(tableStructure[index] == str) break;
            } while(tableStructure[index] != "\0");
            collisionCount--;
            break;

        case doubleHashing:
            j = 0;
            do {
                index = (hash + (j * (aValue - (hash % aValue)))) % tableSize;
                collisionCount++;
                j++;
                if(tableStructure[index] == str) break;
            } while(tableStructure[index] != "\0");
            collisionCount--;
            break;

        default:
            std::cerr << "Error: No Probing method defined, doing nothing.\n";
    }

    std::cout << "The search had " << collisionCount << " collisions\n";
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

std::vector<std::string> findWords(std::string line) {
    std::vector<std::string> words;
    std::string word;
    bool validWord = false;
    words.clear();
    word.clear();
    for(char &chr: line) {
        if(isalpha(chr)) {
            word.push_back(chr);
            validWord = true;
        } else if(validWord) {
            std::transform(word.begin(), word.end(), word.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            if(!word.empty()) {
                words.push_back(word);
            }
            word.clear();
        } else {
            word.clear();
            validWord = false;
        }
    }
    if(!word.empty()) {
        words.push_back(word);
    }
    return words;
}

int main(int argc, char *argv[]) {
    std::ifstream inputFile(argv[1]), queryFile(argv[2]);
    std::string collisionStrategy = argv[4];
    int hashTableSize = atoi(argv[3]), aValue = 0;
    probingMethods probingMethod;
    if(collisionStrategy == "dh") {
        aValue = atoi(argv[5]);
        probingMethod = doubleHashing;
    } else if(collisionStrategy == "lp") {
        probingMethod = linearProbing;
    } else if(collisionStrategy == "qp") {
        probingMethod = quadraticProbing;
    }

    HashTable myHashTable(hashTableSize, probingMethod, aValue);

    std::string curLine;
    int lineCounter = 0, wordCounter = 0;
    std::vector<std::string> wordsInLine;
    //wordsInLine.clear();
    while(std::getline(inputFile, curLine)) {
        lineCounter++;
        wordsInLine = findWords(curLine);
        wordCounter += wordsInLine.size();
        for(std::string &element: wordsInLine) {
            myHashTable.insert(element);
            myHashTable.insertToMap(element, lineCounter);
        }
    }

    std::cout << "The number of words found in the file was " << wordCounter << "\n";
    std::cout << "The number of unique words found in the file was " << myHashTable.mapSize() << "\n";
    std::cout << "The number of collisions was " << myHashTable.totalCollisions << "\n";

    std::string query;
    while(queryFile >> query) {
        std::cout << "\n";
        myHashTable.searchMap(query);
        myHashTable.search(query);
    }

    return 0;
}