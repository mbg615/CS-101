//
// Created by Maddox Guthrie on 4/6/23.
//

#ifndef CS_101_P5_H
#define CS_101_P5_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class HuffmanNode {
public:
    int key;
    char letter;
    std::string huffmanEncoding;
    HuffmanNode *left, *right;

    explicit HuffmanNode(int key);
};

class HuffmanTree {
public:
    HuffmanNode *treeRoot;
    std::unordered_map<char, std::string> encodedLetterPaths;

    void buildHuffmanTree(std::vector<int> const &inorder, std::vector<int> const &level);
    void inOrderTraversal();
    void createCodes();
};

#endif //CS_101_P5_H
