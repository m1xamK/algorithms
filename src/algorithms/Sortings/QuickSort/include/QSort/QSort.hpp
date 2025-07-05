//
// Created by misha on 3/25/23.
//

#ifndef QSORT_H
#define QSORT_H
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <list>
#include <cmath>

template<typename T>
void quick_sort(std::vector<T>& array){
    std::stack<T> stack;
    stack.push(array.size() - 1);
    stack.push(0);
    while(!stack.empty()) {
        int left = stack.top();
        stack.pop();
        int right = stack.top();
        stack.pop();
        if(right <= left)
            continue;
        int i = left - 1;
        int p = left - 1;
        int q = right;
        int j = right;
        T median = array[right];
        for(;;) {
            while(array[++i] < median);
            while(median  < array[--j])
                if (j == left)
                    break;
            if(i >= j)
                break;
            std::swap(array[i], array[j]);
            if(array[i] == median) {
                ++p;
                std::swap(array[p], array[i]);
            }
            if(median == array[j]) {
                --q;
                std::swap(array[q], array[j]);
            }
        }
        std::swap(array[i], array[right]);
        j = i - 1;
        i = i + 1;
        for(int k = left; k <= p; ++k, --j)
            std::swap(array[k], array[j]);
        for(int k = right - 1; k >= q; --k, ++i)
            std::swap(array[k], array[i]);
        stack.push(j);
        stack.push(left);
        stack.push(right);
        stack.push(i);
    }
}



#endif //QSORT_H
