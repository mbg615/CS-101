#include <iostream>

void SwapValues(int& userVal1, int& userVal2, int& userVal3, int& userVal4) {
    int tempVal;
    tempVal = userVal1;
    userVal1 = userVal2;
    userVal2 = tempVal;
    tempVal = userVal3;
    userVal3 = userVal4;
    userVal4 = tempVal;
}

int main() {
    int userVal1, userVal2, userVal3, userVal4;
    std::cin >> userVal1 >> userVal2 >> userVal3 >> userVal4;
    SwapValues(userVal1, userVal2, userVal3, userVal4);
    std::cout << userVal1 << " " << userVal2 << " " << userVal3 << " " << userVal4 << std::endl;

    return 0;
}