#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/**
 * function GenerateSubsets - generate subsets for given sequence
 * @param const std::vector<T> sequence Template sequence
 * @param int** (*function)(int) Functor of Gray code generation function to use

 * @return std::vector<std::vector<T>> Array of generated subsets with Gray code
 */
template<typename T>
std::vector<std::vector<T>> GenerateSubsets(const std::vector<T> sequence, int** (*function)(int)) {
    int size = sequence.size();
    std::vector<std::vector<T>> result;
    std::vector<T> temp;
    int count = 0;
    int** grayCodeArr = function(size);
    for (int i = 0; i < pow(2, size); ++i) {
        for (int j = 0; j < size; ++j) {
            if (grayCodeArr[i][j] == 1) {
                temp.push_back(sequence[j]);
            } else {
                ++count;
            }
        }
        if (count == size) {
            temp = { T() };
        }
        result.push_back(temp);
        temp.clear();
        count = 0;
    }
    for (int i = 0; i < pow(2, size); ++i) {
        delete[] grayCodeArr[i];
    }
    delete[] grayCodeArr;

    return result;
}
