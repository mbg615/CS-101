#include <iostream>
#include <unordered_map>
#include <vector>
#include "queue"

#include "p5.h"

HuffmanNode::HuffmanNode(int key) {
    this->key = key;
    if(key < 128) {
        this->letter = static_cast<char>(key);
    } else {
        this->letter = '\0';
    }

    this->huffmanEncoding.clear();

    this->left = nullptr;
    this->right = nullptr;
}

HuffmanNode* buildTree(std::vector<int> const &inorder, int start, int end, std::unordered_map<int, int> map) {
    if (start > end) {
        return nullptr;
    }

    // find the root node index in sequence `inorder[]` to determine the
    // left and right subtree boundary
    int index = start;
    for (int j = start + 1; j <= end; j++) {
        // Find node with minimum index in level order traversal.
        // That would be the root node of the sequence inorder[start, end]
        if (map[inorder[j]] < map[inorder[index]]) {
            index = j;
        }
    }

    HuffmanNode* root = new HuffmanNode(inorder[index]);

    root->left = buildTree(inorder, start, index - 1, map);

    root->right = buildTree(inorder, index + 1, end, map);

    return root;
}

HuffmanNode* buildTree(std::vector<int> const &inorder, std::vector<int> const &level) {
    int n = inorder.size();

    // create a map to efficiently find the index of an element in a
    // level order sequence
    std::unordered_map<int, int> map;
    for (int i = 0; i < n; i++) {
        map[level[i]] = i;
    }

    // construct the tree and return it
    return buildTree(inorder, 0, n - 1, map);
}

void HuffmanTree::buildHuffmanTree(std::vector<int> const &inorder, std::vector<int> const &level) {
    this->treeRoot = ::buildTree(inorder, level);
}

void inOrderTraversal(HuffmanNode* root) {
    if (root == nullptr) return;

    inOrderTraversal(root->left);
    std::cout << root->key << ":" << root->letter << " ";
    inOrderTraversal(root->right);
}

void HuffmanTree::inOrderTraversal() {
    std::cout << "Inorder traversal of the constructed tree is: ";
    ::inOrderTraversal(this->treeRoot);
}

bool isLeaf(HuffmanNode* node) {
    if(node->left == nullptr && node->right == nullptr) return true;
    return false;
}

void createCodes(HuffmanNode* root, std::string encodedPath, std::unordered_map<char, std::string> &letterPaths){
    if(root == nullptr){
        return;
    }

    if(root->letter != '\0'){
        letterPaths[root->letter] = encodedPath;
    }

    createCodes(root->left, encodedPath + "0", letterPaths);
    createCodes(root->right, encodedPath + "1", letterPaths);
}

void HuffmanTree::createCodes() {
    std::string encodedPath;
    ::createCodes(treeRoot, encodedPath, encodedLetterPaths);

    std::cout << "\n";
    for(auto &element: encodedLetterPaths) {
        std::cout << element.first << ": " << element.second << "\n";
    }


}