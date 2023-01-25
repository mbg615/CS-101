#include <iostream>
#include <vector>

int main() {
    int number;
    std::vector<int> numbers;

    while(std::cin >> number) {
        numbers.push_back(number);
    }

    numbers.erase(numbers.begin());

    int threshold = numbers.back();
    numbers.pop_back();

    for(auto &number: numbers) {
        if(number < threshold) {
            std::cout << number << ",";
        }
    }

    std::cout << std::endl;

    return 0;
}
