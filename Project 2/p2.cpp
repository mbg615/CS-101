//
// Created by Maddox Guthrie on 2/10/23.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

#define DEBUG true

int main(int argc, char *argv[]) {
    std::ifstream fileOne(argv[2]), fileTwo(argv[3]);

    switch(*argv[1]) {
        case 'i':
            {
                std::vector<int> fileOneData, fileTwoData;

                int dataValue;
                while(fileOne >> dataValue) {
                    fileOneData.push_back(dataValue);
                }
                int fileOneDataSorted[fileOneData.size()];
                std::transform(fileOneData.begin(), fileOneData.end(), fileOneDataSorted, [](const int &element){return element;});

                while(fileTwo >> dataValue) {
                    fileTwoData.push_back(dataValue);
                }
                int fileTwoDataSorted[fileTwoData.size()];
                std::transform(fileTwoData.begin(), fileTwoData.end(), fileTwoDataSorted, [](const int &element){return element;});

                void MergeSort(int numbers[], int i, int k);
                MergeSort(fileOneDataSorted, 0,  fileOneData.size() - 1);
                MergeSort(fileTwoDataSorted, 0, fileTwoData.size() - 1);

                int previous = fileOneDataSorted[0] - 100;
                for(int &elementOne: fileOneDataSorted) {
                    for(int &elementTwo: fileTwoDataSorted) {
                        if(elementOne == elementTwo && previous != elementOne) {
                            previous = elementOne;
                            std::cout << elementOne << "\n";
                        }
                    }
                }
            }

            break;

        case 's':
            {
                std::vector<std::string> fileOneData, fileTwoData;

                std::string dataValue;
                while(fileOne >> dataValue) {
                    fileOneData.push_back(dataValue);
                }
                //std::string fileOneDataSorted[fileOneData.size()];
                //std::transform(fileOneData.begin(), fileOneData.end(), fileOneDataSorted, [](const std::string &element){return element;});

                while(fileTwo >> dataValue) {
                    fileTwoData.push_back(dataValue);
                }
                //std::string fileTwoDataSorted[fileTwoData.size()];
                //std::transform(fileTwoData.begin(), fileTwoData.end(), fileTwoDataSorted, [](const std::string &element){return element;});

                std::sort(fileOneData.begin(), fileOneData.end());
                std::sort(fileTwoData.begin(), fileTwoData.end());

                if(DEBUG) {
                    for(std::string &element: fileOneData) {
                        std::cout << element << ", ";
                    }
                    std::cout << "\n";
                }

                if(DEBUG) {
                    for(std::string &element: fileTwoData) {
                        std::cout << element << ", ";
                    }
                    std::cout << "\n";
                }

                std::string previous = "\0";
                for(std::string &elementOne: fileOneData) {
                    for(std::string &elementTwo: fileTwoData) {
                        if(elementOne == elementTwo && previous != elementOne) {
                            previous = elementOne;
                            std::cout << elementOne << "\n";
                        }
                    }
                }

            }

            break;
    }

    return 0;
}

// zyBooks provided merge sort
void Merge(int numbers[], int i, int j, int k) {
    int mergedSize;                            // Size of merged partition
    int mergePos;                              // Position to insert merged number
    int leftPos;                               // Position of elements in left partition
    int rightPos;                              // Position of elements in right partition
    int* mergedNumbers = nullptr;

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;                               // Initialize left partition position
    rightPos = j + 1;                          // Initialize right partition position
    mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
    // for merged numbers

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        if (numbers[leftPos] < numbers[rightPos]) {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
        }
        else {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;

        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
    delete[] mergedNumbers;
}

void MergeSort(int numbers[], int i, int k) {
    int j;

    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        MergeSort(numbers, i, j);
        MergeSort(numbers, j + 1, k);

        // Merge left and right partition in sorted order
        Merge(numbers, i, j, k);
    }
}

// zyBooks quicksort merge sort
int Partition(int numbers[], int i, int k) {
    int l;
    int h;
    int midpoint;
    int pivot;
    int temp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];

    done = false;
    l = i;
    h = k;

    while (!done) {

        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }

    return h;
}

void Quicksort(int numbers[], int i, int k) {
    int j;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k) {
        return;
    }

    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = Partition(numbers, i, k);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    Quicksort(numbers, i, j);
    Quicksort(numbers, j + 1, k);
}
