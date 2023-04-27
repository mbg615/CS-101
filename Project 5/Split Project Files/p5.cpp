#include <iostream>
#include <unordered_map>
#include <vector>

#include "p5.h"

HuffmanNode::HuffmanNode(int key) {
    this->key = key;
    if(key < 128) {
        this->letter = static_cast<char>(key);
    } else {
        this->letter = '#';
    }

    this->left = nullptr;
    this->right = nullptr;
}

HuffmanNode* buildTree(std::vector<int> const &inorder, int start, int end, std::unordered_map<int, int> map) {
    if (start > end) {
        return nullptr;
    }

    int index = start;
    for (int i = start + 1; i <= end; i++) {
        if (map[inorder[i]] < map[inorder[index]]) {
            index = i;
        }
    }

    auto root = new HuffmanNode(inorder[index]);

    root->left = buildTree(inorder, start, index - 1, map);

    root->right = buildTree(inorder, index + 1, end, map);

    return root;
}

void HuffmanTree::buildHuffmanTree(std::vector<int> const &inorder, std::vector<int> const &level) {
    int size = (int)inorder.size();

    std::unordered_map<int, int> map;
    for (int i = 0; i < size; i++) {
        map[level[i]] = i;
    }

    this->treeRoot = buildTree(inorder, 0, size - 1, map);
}

void inOrderTraversal(HuffmanNode* root) {
    if (root == nullptr) return;

    inOrderTraversal(root->left);
    if(root->letter == '\n') {
        std::cout << root->key << ":" << "\\n ";
    } else {
        std::cout << root->key << ":" << root->letter << " ";
    }
    inOrderTraversal(root->right);
}

void HuffmanTree::inOrderTraversal() const {
    std::cout << "Inorder traversal of the constructed tree is: ";
    ::inOrderTraversal(this->treeRoot);
}

void HuffmanTree::decodeText(std::string &encodedText) const {
    HuffmanNode* currentTreeNode = treeRoot;
    for(char i : encodedText) {
        if(currentTreeNode->left == nullptr && currentTreeNode->right == nullptr) {
            std::cout << currentTreeNode->letter << std::flush;
            currentTreeNode = treeRoot;
        }

        if(i == '0') {
            currentTreeNode = currentTreeNode->left;
        } else if(i == '1') {
            currentTreeNode = currentTreeNode->right;
        }
    }
    std::cout << currentTreeNode->letter;
}