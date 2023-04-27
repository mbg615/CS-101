//
// Created by Maddox Guthrie on 4/6/23.
//

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>

#include "p5.h"

int main([[maybe_unused]] int argc, char** argv) {
    std::ifstream inOrderTransversal(argv[1]);
    std::ifstream levelOrderTraversal(argv[2]);
    std::ifstream encodedText(argv[3]);

    std::vector<int> inOrderVector, levelOrderVector;

    int nodeValue;
    while (inOrderTransversal >> nodeValue) {
        inOrderVector.push_back(nodeValue);
    }
    inOrderTransversal.close();

    while (levelOrderTraversal >> nodeValue) {
        levelOrderVector.push_back(nodeValue);
    }
    levelOrderTraversal.close();

    auto myHuffmanTree = new HuffmanTree;

    myHuffmanTree->buildHuffmanTree(inOrderVector, levelOrderVector);

    myHuffmanTree->inOrderTraversal();

    std::string stringPath;
    stringPath.clear();
    while(std::getline(encodedText, stringPath)) {
        myHuffmanTree->decodeText(stringPath);
        stringPath.clear();
    }

    return 0;
}