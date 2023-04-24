//
// Created by Maddox Guthrie on 4/6/23.
//

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "p5.h"

// TODO: https://www.techiedelight.com/construct-binary-tree-from-inorder-level-order-traversals/

int main(int argc, char** argv) {
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

    HuffmanTree* myHuffmanTree = new HuffmanTree;

    myHuffmanTree->buildHuffmanTree(inOrderVector, levelOrderVector);

    myHuffmanTree->inOrderTraversal();

    myHuffmanTree->createCodes();

    return 0;
}