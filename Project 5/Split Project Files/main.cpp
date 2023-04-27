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

    int inOrder[inOrderVector.size()];
    for(int i = 0; i < static_cast<int>(inOrderVector.size()); i++) {
        inOrder[i] = inOrderVector.at(i);
    }

    int levelOrder[levelOrderVector.size()];
    for(int i = 0; i < static_cast<int>(levelOrderVector.size()); i++) {
        levelOrder[i] = levelOrderVector.at(i);
    }

    auto myHuffmanTree = new HuffmanTree;

    myHuffmanTree->buildHuffmanTree(inOrder, levelOrder, 0, static_cast<int>(inOrderVector.size()), static_cast<int>(levelOrderVector.size()));

    char shiftDir;
    std::string encodedPath;
    while(encodedText >> shiftDir) {
        encodedPath.push_back(shiftDir);
    }
    encodedText.close();

    myHuffmanTree->decodeText(encodedPath);

    return 0;
}