#include <iostream>
#include "Triangle.h"

int main() {
    Triangle triangle1;
    Triangle triangle2;

    double base, height;
    std::cin >> base >> height;
    triangle1.SetBase(base);
    triangle1.SetHeight(height);

    std::cin >> base >> height;
    triangle2.SetBase(base);
    triangle2.SetHeight(height);

    cout << "Triangle with smaller area:" << endl;

    if(triangle1.GetArea() < triangle2.GetArea()) {
        triangle1.PrintInfo();
    } else {
        triangle2.PrintInfo();
    }

    return 0;
}