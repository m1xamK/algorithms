#ifndef BINARYSEARCH_RECURSIVE_H
#define BINARYSEARCH_RECURSIVE_H

#include <vector>

template <typename T>
int binarySearchRecursive(const std::vector<T>& arr, int left, int right, const T& key) {
    if (left > right)
        return -1;

    int mid = left + (right - left) / 2;

    if (arr[mid] == key)
        return mid;
    else if (arr[mid] > key)
        return binarySearchRecursive(arr, left, mid - 1, key);
    else
        return binarySearchRecursive(arr, mid + 1, right, key);
}

#endif // BINARYSEARCH_RECURSIVE_H