#ifndef MP_DDZ_SHELLSORT_H
#define MP_DDZ_SHELLSORT_H
#include <vector>

/*
 *  arr - Sortable array
 *  gap - Array of gap lengths
 * */
template <typename T>
void shellSort(std::vector<T>&arr, std::vector<int>gap) {
    int arrNum = arr.size();
    int gapNum = gap.size();
    --gapNum;
    for (; gapNum >= 0; --gapNum) {
        for (int i = gap[gapNum]; i < arrNum; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap[gapNum] && arr[j - gap[gapNum]] > temp; j -= gap[gapNum]) {
                arr[j] = arr[j - gap[gapNum]];
            }
            arr[j] = temp;
        }
    }
}
#endif //MP_DDZ_SHELLSORT_H
