//
// Created by Maddox Guthrie on 1/31/23.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cctype>

#define DEBUG true

int main(int argc, char *argv[]) {
    if(DEBUG && argc != 4) {
        std::cout << "Invalid number of arguments [" << argc - 1 << "] given expected [3]\n";
        exit(-1);
    }

    // Open the cipher file
    std::ifstream cipherFile;
    cipherFile.open(argv[1]);
    if(!cipherFile.is_open()) {
        std::cout << "ERROR: Could not open" << argv[1] << std::endl;
    }

    // Open the encoded text file
    std::ifstream encodedTextFile;
    encodedTextFile.open(argv[2]);
    if(!cipherFile.is_open()) {
        std::cout << "ERROR: Could not open" << argv[2] << std::endl;
    }

    std::string givenWord = argv[3];

    std::string mapLine, keyLine;
    getline(cipherFile, mapLine);
    getline(cipherFile, keyLine);

    std::map<char, char> cipher;

    for(int i = 0; i < mapLine.length(); i++) {
        cipher.insert(std::pair<char,char>(keyLine[i],mapLine[i]));
    }

    if(DEBUG) {
        std::cout << "KEY:\tMAP:\n";
        for (auto const &pair: cipher) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
        std::cout << "\n\n";
    }

    std::string encodedStr;

    std::map<char,char>::iterator it;
    while(std::getline(encodedTextFile, encodedStr)) {
        std::string partiallyDecodedStr;
        std::string decodedStr;

        if(DEBUG) {
            std::cout << "Encoded Text:\n" << encodedStr << "\n";
        }

        for(char &ch: encodedStr) {
            it = cipher.find(ch);
            if(it != cipher.end()) {
                partiallyDecodedStr.push_back(it->second);
                decodedStr.push_back(it->second);
            } else {
                partiallyDecodedStr.push_back(ch);
                if(isalpha(ch)) {
                    decodedStr.push_back('_');
                } else {
                    decodedStr.push_back(ch);
                }
            }
        }

        if(DEBUG) {
            std::cout << "Partially Decoded Text:\n" << partiallyDecodedStr << "\n";
            std::cout << "Decoded Text:\n" << decodedStr << "\n\n\n";
        }

        std::vector<std::string> tokenizeStr(std::string str);
        std::vector tokenizedDecodedStr = tokenizeStr(decodedStr);
        std::vector tokenizedPartiallyDecodedStr = tokenizeStr(partiallyDecodedStr);

        int findIndexOfElement(std::string &keyWord, std::vector<std::string> &tokenizedStr);
        std::cout << findIndexOfElement(givenWord, tokenizedDecodedStr) << "\n";

        if(DEBUG) {
            for(auto &token: tokenizedDecodedStr) {
                std::cout << token << ", ";
            }
            std::cout << "\n";

            for(auto &token: tokenizedPartiallyDecodedStr) {
                std::cout << token << ", ";
            }
            std::cout << "\n";
        }

        std::cout << decodedStr << "\n"; // Required output
    }

    return 0;
}

std::vector<std::string> tokenizeStr(std::string strToTokenize) {
    std::vector<std::string> tokenizedStr;
    std::string token;

    for(char &ch: strToTokenize) {
        if(isalpha(ch) || ch == '_') {
            token.push_back(ch);
        } else {
            tokenizedStr.push_back(token);
            token.clear();
            continue;
        }
    }

    tokenizedStr.push_back(token);
    return tokenizedStr;
}

int findIndexOfElement(std::string &keyWord, std::vector<std::string> &tokenizedStr) {
    int positionCounter = 0;
    for(std::string &token: tokenizedStr) {
        if(token.length() == keyWord.length()) {
            bool isValidPosition = true;

            for(int i = 0; i < keyWord.length(); i++) {
                if(token.at(i) == keyWord.at(i) || token.at(i) == ' ') {
                    continue;
                } else {
                    isValidPosition = false;
                    break;
                }
            }

            if(isValidPosition) {
                return positionCounter;
            }
        }

        positionCounter++;
    }

    return -1;
}