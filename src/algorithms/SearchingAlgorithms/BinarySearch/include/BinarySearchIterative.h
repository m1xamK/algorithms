#ifndef BINARYSEARCH_ITERATIVE_H
#define BINARYSEARCH_ITERATIVE_H

#include <vector>

template <typename T>
int binarySearchIterative(const std::vector<T>& arr, const T& key) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

#endif // BINARYSEARCH_ITERATIVE_H