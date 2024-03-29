#include <string>
#include <iostream>
#include <sstream>

#include "triple.h"

using namespace std;

// all elements have value 0
// usage: Triple t;
Triple::Triple() {
    a = 0;
    b = 0;
    c = 0;
}

// all elements have value k
// usage: Triple t(int);
Triple::Triple(int k) {
    a = k;
    b = k;
    c = k;
}


// a has value x, b has value y, c has value z
// usage: Triple t(int, int, int);
Triple::Triple(int x, int y, int z) {
	a = x;
    b = y;
    c = z;
}

// index 0 is a, 1 is b, 2 is c
// usage: int i = t.fetch(int);
int Triple::fetch(int index) {
    if(index == 0) {
        return a;
    } else if(index == 1) {
        return b;
    } else if(index == 2) {
        return c;
    }
   return -1;
}

// update chosen element to value k
// index 0 is a, 1 is b, 2 is c
// usage: t.assign(int, int);
void Triple::assign(int index, int k) {
    if(index == 0) {
        a = k;
    } else if(index == 1) {
        b = k;
    } else if(index == 2) {
        c = k;
    }
}

// string representation is "(a,b,c)"
// write fromString() first and use it
// this method has already been written for you
// usage: Triple t("(1,2,3)");
Triple::Triple(string s) {
   fromString(s);
}

// create a string representation of the vector: "(a,b,c)"
// use to_string(int) which returns the int as a string
// usage: string s = t.toString();
string Triple::toString() {
    std::string tripleAsString = "(" + to_string(a) + "," + to_string(b) + "," + to_string(c) + ")";
    return tripleAsString;
}

// change the vector to equal the string representation: "(a,b,c)"
// this method has already been written for you
// usage: t.fromString("(1,2,3)");
void Triple::fromString(string s) {
	istringstream ss(s); // c++ class version of sscanf() - ostringstream is like sprintf()
	char leftparen, comma1, comma2, rightparen;
	ss >> leftparen >> a >> comma1 >> b >> comma2 >> c >> rightparen;
}

// return the largest element value
// usage: int i = t.maxElement();
int Triple::maxElement() {
    if(a >= b && a >= c) {
        return a;
    } else if(b >= a && b >= c) {
        return b;
    } else if(c >= a && c >= b) {
        return c;
    }
    return 0;
}

// return sum of the element values
// usage: int i = t.sum();
int Triple::sum() {
    return a + b + c;
}

// return product of the element values
// usage: int i = t.product();
// example: int i = Triple(1,2,3).product(); // 1*2*3 = 6
int Triple::product() {
    return a * b * c;
}

// add the vectors and return the new resulting vector
// usage: Triple t3 = t1 + t2;
// example: Triple t3 = Triple(1,2,3) + Triple(4,5,6); // t3 == (5,7,9)
Triple Triple::operator+(Triple t) const {
   return Triple(a + t.fetch(0), b + t.fetch(1), c + t.fetch(2));
}

// add the "right hand side" vector to the local "left hand side" vector
// this function does not return anything because the left hand side is modified
// think about "int a = 1; a += 2;", nothing is returned from "+= 2", "a" is changed directly
// usage: t1 += t2;
void Triple::operator+=(Triple t) {
    a += t.a;
    b += t.b;
    c += t.c;
}

// multiply vector elements by int value and return the new vector
// usage: Triple t2 = t1 * int;
// usage: Triple t2 = Triple(1,2,3) * 3; // t2 == (3,6,9)
Triple Triple::operator*(int k) const {
   return Triple(a * k, b * k, c * k);
}


// multiply vector elements by int value
// this function does not return anything because the vector is modified
// usage: t *= int;
void Triple::operator*=(int k) {
    a *= k;
    b *= k;
    c *= k;
}

// vector dot product
// usage: int i = t.dotProduct(t2);
// example int i = Triple(1,2,3).dotProduct( Triple(4,5,6) ); // i == (1*4 + 2*5 + 3*6) == 32
int Triple::dotProduct(Triple t) {
    return ((a * t.a) + (b * t.b) + (c * t.c));
}

// reverse the order of the vector elements and return the new vector
// usage: Triple t2 = t1.reverse();
// example: Triple t2 = Triple(1,2,3).reverse(); // t2 == (3,2,1)
Triple Triple::reverse() const {
   return Triple(c, b, a);
}

// reverse the order of the vector elements
// usage: t.reverseInPlace();
void Triple::reverseInPlace() {
    int temp = a;
    a = c;
    c = temp;
}

// do both vectors contain the same values?
// usage: bool b = (t1 == t2);
bool Triple::operator==(Triple t) {
    if(a == t.a && b == t.b && c == t.c) {
        return true;
    }
   return false;
}

// usage: bool b = (t1 != t2);
bool Triple::operator!=(Triple t) {
    if(a != t.a || b != t.b || c != t.c) {
        return true;
    }
   return false;
}

// write the string representation of the vector to the stream
// the stream representation is "(a,b,c)"
// use toString()
// usage: cout << t << endl;
ostream &operator<<(ostream &os, Triple t) {
    os << t.toString();
   return os;
}

// create a vector by reading from the stream
// the stream representation is "(a,b,c)"
// >> a char, then an int, then a ...
// usage: cin >> t;
istream &operator>>(istream &is, Triple &t) {
    char temp;
    is >> temp >> t.a >> temp >> t.b >> temp >> t.c;
   return is;
}
