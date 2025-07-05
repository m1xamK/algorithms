#ifndef HEAPSORT_HEAPSORT_HPP
#define HEAPSORT_HEAPSORT_HPP

#include <iostream>

template<typename T>
void heapify(T* arr, int size, int i)
{
    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < size && arr[l] > arr[largest])
        largest = l;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < size && arr[r] > arr[largest])
        largest = r;

    // Если самый большой элемент не корень
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, size, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
template<typename T>
void heapSort(T* arr, int size)
{
    // Построение кучи (перегруппируем массив)
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = size - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        std::swap(arr[0], arr[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

#endif