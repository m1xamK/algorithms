#include "../include/SubsetsWithGreyCode/SubsetsWithGreyCode.hpp"


/**
 * function GrayCode - generate Gray Code
 * @param const int size Size of Gray code to be generated

 * @return int** Array of generated Gray codes
 */
int** GrayCode(const int size) {
    int rowsCount;
    int columnsCount = size;
    int** result = new int* [ rowsCount = int(pow(2, size))] {};
    for (int i = 0; i < rowsCount; ++i) {
        result[i] = new int [columnsCount] {};
    }
    int* arr = new int [size + 1] {};
    int j = 0;
    int index = 0;
    while (j < size) {
        int* reverseArr = new int [size] {};
        for (int i = 0; i < size; ++i) {
            reverseArr[i] = arr[i];
        }
        std::reverse(reverseArr + 0, reverseArr + size);
        result[index++] = reverseArr;
        arr[size] = 1 - arr[size];
        if (arr[size] == 1) {
            j = 0;
        } else {
            for (int i = 0; i < size; ++i) {
                if (arr[i] == 1) {
                    j = i + 1;
                    break;
                }
            }
        }
        arr[j] = 1 - arr[j];
    }
    delete[] arr;

    return result;
}


/**
 * function RecursiveGrayCode - recursively generate Gray Code
 * @param const int size Size of Gray code to be generated

 * @return int** Array of generated Gray codes
 */
int** RecursiveGrayCode(const int size) {
    int rowsCount;
    int columnsCount = size;
    int** result = new int* [ rowsCount = int(pow(2, size))] {};
    for (int i = 0; i < rowsCount; ++i) {
        result[i] = new int [columnsCount] {};
    }
    int* arr = new int [size + 1] {};
    RecursiveIterationOfGrayCode(size, result, arr, 0, 0);
    delete[] arr;

    return result;
}


/**
 * function RecursiveIterationOfGrayCode - recursive iteration for Gray Code generation
 * @param const int size Size of Gray code to be generated
 * @param int**& result Array of generated Gray codes, passed by reference
 * @param int* arr Additional array, used to generate Gray code
 * @param int j Additional variable-index, used to generate Gray code
 * @param int index Index of insertion point
 */
void RecursiveIterationOfGrayCode(const int size, int**& result, int* arr, int j, int index) {
    if (j >= size) {
        return;
    }
    int* reverseArr = new int [size] {};
    for (int i = 0; i < size; ++i) {
        reverseArr[i] = arr[i];
    }
    std::reverse(reverseArr + 0, reverseArr + size);
    result[index++] = reverseArr;
    arr[size] = 1 - arr[size];
    if (arr[size] == 1) {
        j = 0;
    } else {
        for (int i = 0; i < size; ++i) {
            if (arr[i] == 1) {
                j = i + 1;
                break;
            }
        }
    }
    arr[j] = 1 - arr[j];
    RecursiveIterationOfGrayCode(size, result, arr, j, index);
}
