#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

void inOrderTraversal(HuffmanNode* root) {
    if (root == nullptr) return;

    inOrderTraversal(root->left);
    std::cout << root->key << " ";
//    if(root->letter == '\n') {
//        std::cout << root->key << ":" << "\\n ";
//    } else {
//        std::cout << root->key << ":" << root->letter << " ";
//    }
    inOrderTraversal(root->right);
}

void HuffmanTree::inOrderTraversal() const {
    std::cout << "Inorder traversal of the constructed tree is: ";
    ::inOrderTraversal(this->treeRoot);
}

int searchForIndex(const int* inOrder, int inLeft, int inRight, int value) {
    for(int i = inLeft; i <= inRight; i++) {
        if(inOrder[i] == value) {
            return i;
        }
    }
    return -1;
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

HuffmanNode* buildHuffmanTree(int* inOrder, int* levelOrder, int inLeft, int inRight, int levelSize) {
    if(inRight < inLeft || levelSize <= 0) {
        return nullptr;
    }

    auto* root = new HuffmanNode(levelOrder[0]);

    int inOrderIndex = searchForIndex(inOrder, inLeft, inRight, levelOrder[0]);

    int rightSize = 0, leftSize = 0;
    std::vector<int> leftSide, rightSide;
    for(int i = 1; i < levelSize; i++) {
        if(searchForIndex(inOrder, 0, inOrderIndex - 1, levelOrder[i]) != -1) {
            leftSide.push_back(levelOrder[i]);
            leftSize++;
        } else {
            rightSide.push_back(levelOrder[i]);
            rightSize++;
        }
    }

    int left[leftSize], right[rightSize];
    for(int i = 0; i < leftSize; i++) {
        left[i] = leftSide.at(i);
    }

    for(int i = 0; i < rightSize; i++) {
        right[i] = rightSide.at(i);
    }

    root->left = buildHuffmanTree(inOrder, left, inLeft, inOrderIndex - 1, leftSize);
    root->right = buildHuffmanTree(inOrder, right, inOrderIndex + 1, inRight, rightSize);

    return root;

}

void HuffmanTree::buildHuffmanTree(int* inOrder, int* levelOrder, int inLeft, int inRight, int levelSize) {
    this->treeRoot = ::buildHuffmanTree(inOrder, levelOrder, inLeft, inRight, levelSize);
}

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