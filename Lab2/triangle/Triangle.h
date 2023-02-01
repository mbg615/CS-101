//
// Created by Maddox Guthrie on 1/25/23.
//

#ifndef CS_101_TRIANGLE_H
#define CS_101_TRIANGLE_H

class Triangle {
private:
    double base;
    double height;

public:
    void SetBase(double userBase);
    void SetHeight(double userHeight);
    double GetArea() const;
    void PrintInfo() const;
};

#endif //CS_101_TRIANGLE_H
