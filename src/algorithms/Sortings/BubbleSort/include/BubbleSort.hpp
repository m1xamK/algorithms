#ifndef BUBBLESORT_BUBBLESORT_H
#define BUBBLESORT_BUBBLESORT_H
#include <vector>
#include <algorithm>

namespace BubbleSort
{

    template <typename T>
    void Sort(std::vector<T> &array)
    {
        bool swapped;
        for (size_t i = 0; i < array.size() - 1; ++i)
        {
            swapped = false;
            for (size_t j = 0; j < array.size() - i - 1; ++j)
            {
                if (array[j] > array[j + 1])
                {
                    std::swap(array[j], array[j + 1]);
                    swapped = true;
                }
            }
            // Если на текущей итерации не было перестановок, массив уже отсортирован
            if (!swapped)
                break;
        }
    }

}

#endif // BUBBLESORT_BUBBLESORT_H