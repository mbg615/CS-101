#include <string>
#include <iostream>
#include <fstream>

#include "p4.h"

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
    int lineCounter = 0;
    std::vector<std::string> wordsInLine;
    //wordsInLine.clear();
    while(std::getline(inputFile, curLine)) {
        lineCounter++;
        wordsInLine = findWords(curLine);
        for(std::string &element: wordsInLine) {
            myHashTable.insert(element);
            myHashTable.insertToMap(element, lineCounter);
        }
    }

    myHashTable.print();

    return 0;
}





