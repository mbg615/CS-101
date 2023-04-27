//
// Created by Maddox Guthrie on 4/6/23.
//

#ifndef CS_101_P5_H
#define CS_101_P5_H

#include <vector>
#include <string>
#include <unordered_map>

class HuffmanNode {
public:
    int key;
    char letter;
    HuffmanNode *left, *right;

    explicit HuffmanNode(int key);
};

class HuffmanTree {
public:
    HuffmanNode *treeRoot;

    void buildHuffmanTree(int* inOrder, int* levelOrder, int inLeft, int inRight, int levelSize);
    void inOrderTraversal() const;
    void decodeText(std::string &encodedText) const;

};

#endif //CS_101_P5_H
