#include <iostream>
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<char>& v) {
    for(const char &element: v) {
        os << " " << element;
    }
    return os;
}

int main(int argc, char *argv[]) {
    std::vector<char> pseudoStack;
    std::string pairsToCheck = argv[1];
    for(char &chr: pairsToCheck) {
        std::cout << "Stack: " << pseudoStack << "\n";
        std::cout << "Character: " << chr << "\n";
        if(chr == '(' || chr == '[' || chr == '{' || chr == '<') {
            std::cout << "Push\n";
            pseudoStack.push_back(chr);
        } else if(chr == ')' || chr == ']' || chr == '}' || chr == '>') {
            if(pseudoStack.back() == '(' && chr == ')') {
                std::cout << "Matching ( and )\nPop\n";
                pseudoStack.pop_back();
            } else if(pseudoStack.back() == '[' && chr == ']') {
                std::cout << "Matching [ and ]\nPop\n";
                pseudoStack.pop_back();
            } else if(pseudoStack.back() == '{' && chr == '}') {
                std::cout << "Matching { and }\nPop\n";
                pseudoStack.pop_back();
            } else if(pseudoStack.back() == '<' && chr == '>') {
                std::cout << "Matching < and >\nPop\n";
                pseudoStack.pop_back();
            } else {
                if(pseudoStack.empty()) {
                    std::cout << "Error: unmatched right symbol " << chr << "\n";
                    exit(0);
                } else {
                    std::cout << "Error: mismatched pair " << pseudoStack.back() << " and " << chr;
                    exit(0);
                }
            }
        } else {
            std::cout << "Error: invalid character " << chr << "\n";
            exit(0);
        }
    }
    std::cout << "Stack: " << pseudoStack << "\n";
    std::cout << "Reached end of string\n";
    if(!pseudoStack.empty()) {
        std::cout << "Error: unmatched left symbol " << pseudoStack.back() << "\n";
    } else {
        std::cout << "String is properly balanced\n";
    }
}