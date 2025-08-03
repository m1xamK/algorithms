#include <vector>
#include "../src/DDZ_MonkeySort.cpp"

template<typename T>
bool isSorted(const std::vector<T>& arr);

template<typename T>
void shuffleArray(std::vector<T>& arr);

template<typename T>
void MonkeySort(std::vector<T>& arr);

template void MonkeySort<int>(std::vector<int>&);
template void MonkeySort<double>(std::vector<double>&);