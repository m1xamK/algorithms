#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
template<typename T>
bool isSorted(const std::vector<T>& arr) {
    if (arr.empty() || arr.size() == 1) {
        return true;
    }
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

template<typename T>
void shuffleArray(std::vector<T>& arr) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (size_t i = 0; i < arr.size(); ++i) {
        size_t j = rand() % arr.size();
        std::swap(arr[i], arr[j]);
    }
}

template<typename T>
void MonkeySort(std::vector<T>& arr) {
    while (!isSorted(arr)) {
        shuffleArray(arr);
    }
}

// Явное инстанцирование для нужных типов
