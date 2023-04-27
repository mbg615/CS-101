#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

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
    std::unordered_map<std::string, char> encodedLetterPaths;

    void buildHuffmanTree(std::vector<int> const &inorder, std::vector<int> const &level);
    void createCodes();

    void inOrderTraversal() const;
    void decodeText(std::string &encodedText) const;
};

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

    auto* root = new HuffmanNode(inorder[index]);

    root->left = buildTree(inorder, start, index - 1, map);

    root->right = buildTree(inorder, index + 1, end, map);

    return root;
}

HuffmanNode* buildTree(std::vector<int> const &inorder, std::vector<int> const &level) {
    int n = (int)inorder.size();

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

void HuffmanTree::inOrderTraversal() const {
    std::cout << "Inorder traversal of the constructed tree is: ";
    ::inOrderTraversal(this->treeRoot);
}

void createCodes(HuffmanNode* root, std::string encodedPath, std::unordered_map<std::string, char> &letterPaths){
    if(root == nullptr){
        return;
    }

    if(root->letter != '$'){
        letterPaths[encodedPath] = root->letter;
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

void HuffmanTree::decodeText(std::string &encodedText) const {
    HuffmanNode* currentTreeNode = treeRoot;
    char testVal;
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

    auto myHuffmanTree = new HuffmanTree;

    myHuffmanTree->buildHuffmanTree(inOrderVector, levelOrderVector);

    //myHuffmanTree->inOrderTraversal();

    std::string stringPath;
    stringPath.clear();
    while(std::getline(encodedText, stringPath)) {
        myHuffmanTree->decodeText(stringPath);
        stringPath.clear();
    }

    return 0;
}