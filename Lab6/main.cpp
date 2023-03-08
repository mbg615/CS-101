#include <iostream>

#include "MyDynamicArray.cpp"

using namespace std;

void foo(MyDynamicArray param) {
    for(int i=0; i<param.length(); i++) 
        param[i]=0;
}

int main() {
    MyDynamicArray x;
    for (int i=0; i<130; i++) {
        x.add(i);
    }
    int sum = 0;
    for (int i=0; i<x.length(); i++) {
        sum+=x[i];
    }   
    cout << "The sum is : " << sum << endl;
    for (int i=0; i<125; i++)
        x.del();
    x[10] = 27;
    
    MyDynamicArray y(100);
    for (int i=0; i<y.length(); i+=2) y[i] = i*i;
    for (int i=0; i<200; i++) {
        y.add(i);
    }
    sum = 0;
    for (int i=0; i<y.length(); i+=2) {
        sum+=y[i];
    }   
    cout << "The sum is : " << sum << endl;
    for (int i=0; i<195; i++)
        y.del();
    y[60] = 27;
    for (int i=0; i<200; i++) {
        y.add(i);
    }
    sum = 0;
    for (int i=0; i<y.length(); i+=2) {
        sum+=y[i];
    }   
    cout << "The sum is : " << sum << endl;
    MyDynamicArray z(10);
    z[9] = 1000;
    cout << z.length() << endl;
    z.clear();
    z[2] = 5;
    z.add(9);
    z.add(5);
    cout << z.length() << endl;
    
    MyDynamicArray b;
    b = x;
    x[1] += 100;
    
    sum = 0;
    for (int i=0; i<x.length(); i++) {
        sum+=x[i];
    }   
    cout << "The x sum is : " << sum << endl;
    
    sum = 0;
    for (int i=0; i<b.length(); i++) {
        sum+=b[i];
    }   
    cout << "The b sum is : " << sum << endl;   
    
    foo(b);
    
    sum = 0;
    for (int i=0; i<b.length(); i++) {
        sum+=b[i];
    }   
    cout << "The b sum is : " << sum << endl;
    
    return 0;
}
