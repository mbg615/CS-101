#include <iostream>

class MyDynamicArray {
private:
    int size, capacity, error;
    int *a;
public:
    MyDynamicArray() {
        capacity = 2;
        size = 0;
        error = 0;
        a = new int[capacity];
    }
    MyDynamicArray(int s) {
        /* Your code goes here */
        capacity = s;
        size = s;
        error = 0;
        a = new int[capacity];
    }
    int& operator[](int i){
        /* Your code goes here */
        if(i >= size) {
            std::cout << "Out of bounds reference : " << i << "\n";
            return error;
        } else {
            return a[i];
        }
    }
    void add(int v) {
        /* Your code goes here */
        if(size == capacity) {
            std::cout << "Doubling to : " << capacity * 2 << "\n";
            int *anew;
            anew = new int[capacity * 2];
            for(int i = 0; i < size; i++) {
                anew[i] = a[i];
            }
            for(int i = size; i < capacity * 2; i++) {
                anew[i] = 0;
            }
            capacity *= 2;
            a = anew;
            a[size++] = v;
        } else {
            a[size++] = v;
        }
    }
    void del() {
        /* Your code goes here */
        a[size] = 0;
        size--;
        if(size <= capacity / 4) {
            std::cout << "Reducing to : " << capacity / 2 << "\n";
            int *anew;
            anew = new int[capacity / 2];
            for(int i = 0; i < size; i++) {
                anew[i] = a[i];
            }
            for(int i = size; i < capacity / 2; i++) {
                anew[i] = 0;
            }
            capacity /= 2;
        }
    }
    int length() {
        return size;
    }
    void clear() {
        delete[] a;
        size = 0;
        capacity = 2;
        error = 0;
        a = new int[capacity];
    }
};
