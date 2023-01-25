#include <iostream>
#include <cstring>
#include <fstream>

int main() {
    std::string fileToOpen;
    std::cin >> fileToOpen;
    std::string fileName;
    std::ifstream inFile;
    inFile.open(fileToOpen);

    while(std::getline(inFile, fileName)) {
        fileName.erase(fileName.find("photo.jpg"));
        fileName.append("info.txt");
        std::cout << fileName << "\n";
    }

    return 0;
}
