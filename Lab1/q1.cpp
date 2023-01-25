#include <iostream>
#include <string>

int main() {
    int userInt;
    double userDouble;
    char userChar;
    std::string userString;

    std::cout << "Enter integer:\n";
    std::cin  >> userInt;

    std::cout << "Enter double:\n";
    std::cin >> userDouble;

    std::cout << "Enter character:\n";
    std::cin >> userChar;

    std::cout << "Enter string:\n";
    std::cin >> userString;

    std::cout << userInt << " " << userDouble << " " << userChar << " " << userString << "\n";
    std::cout << userString << " " << userChar << " " << userDouble << " " << userInt << "\n";
    std::cout << userDouble << " cast to an integer is " << int(userDouble) << std::endl;

    return 0;
}