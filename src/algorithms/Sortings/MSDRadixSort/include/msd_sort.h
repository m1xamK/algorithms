// msd_sort.h
#ifndef MSD_SORT_H
#define MSD_SORT_H

#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <climits>

namespace msd {

/**
 * Реализация поразрядной сортировки (Radix Sort) начиная со старшего разряда (MSD)
 * Работает с итераторами произвольного доступа и целочисленными типами
 * 
 * @tparam RandomIt - тип итератора произвольного доступа
 * @param first - итератор на первый элемент
 * @param last - итератор на элемент, следующий за последним
 * @param digit - текущая позиция бита для сортировки (по умолчанию - старший бит)
 */
template <typename RandomIt>
void msd_radix_sort(RandomIt begin, RandomIt end, int bit = sizeof(typename std::iterator_traits<RandomIt>::value_type) * 8 - 1)
{
    if (begin == end || std::next(begin) == end || bit < 0) {
        return;
    }

    // Определяем тип элементов, на которые указывают итераторы
    using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    
    // Для последнего разряда (знакового бита) делаем особую проверку
    auto pivot = std::partition(begin, end, [bit](ValueType value) {
        if constexpr (std::is_signed_v<ValueType>) {
            if (bit == sizeof(ValueType) * 8 - 1) {
                return value >= 0;
            }
        }
        return !(value & (ValueType{1} << bit));
    });

    msd_radix_sort(begin, pivot, bit - 1);
    msd_radix_sort(pivot, end, bit - 1);
}

} // namespace msd

#endif // MSD_SORT_H