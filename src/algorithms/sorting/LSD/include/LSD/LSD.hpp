#ifndef LSD_LSD_H
#define LSD_LSD_H

#include <vector>
#include <string>


void LSDSort(std::vector <std::string >& arr)
{
    int n = arr.size();
    const int R = 256; //footing 
    std::vector<std::string> aux(n);
    int radix = 0;
    for (int i = 0; i < n; ++i)
    {
        int sizeWord = arr[i].length();
        radix = (sizeWord > radix) ? sizeWord : radix;

    }
    for (int d = radix - 1; d >= 0; --d) {
        std::vector<int> count(R + 1, 0);

        // we count the frequency of each character in the position d 
        for (int i = 0; i < n; ++i) {
            count[arr[i][d] + 1]++;
        }

        // the calculation is summed up 
        for (int r = 0; r < R; ++r) {
            count[r + 1] += count[r];
        }

        // moving the rows to sorted positions 
        for (int i = 0; i < n; ++i) {
            aux[count[arr[i][d]]++] = arr[i];
        }

        // copy back to the original array 
        for (int i = 0; i < n; ++i) {
            arr[i] = aux[i];
        }
    }

}
#endif //LSD_LSD_H
