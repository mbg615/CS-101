#include <iostream>
#include <std::string>

std::string RemoveNonAlpha(string userString) {
    std::string resultString;
    for(auto &ch: userString) {
        if(isalpha(ch)) {
            resultString.push_back(ch);
        }
    }
    return resultString;
}

int main() {
    std::string userString;
    std::getline(std::cin, userString);
    std::cout << RemoveNonAlpha(userString) << std::endl;

    return 0;
}
