#ifndef SUBSETSWITHGREYCODE_SUBSETSWITHGREYCODE_H
#define SUBSETSWITHGREYCODE_SUBSETSWITHGREYCODE_H

#include <algorithm>
#include <cmath>

int** GrayCode(const int size);
int** RecursiveGrayCode(const int size);
void RecursiveIterationOfGrayCode(const int size, int**& result, int* arr, int j, int index);

#include "GenerateSubsets.hpp"

#endif //SUBSETSWITHGREYCODE_SUBSETSWITHGREYCODE_H
