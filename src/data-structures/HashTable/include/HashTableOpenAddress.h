#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
#include <string>
using namespace std;

template<typename T>
class HashTableOpenAddressing {
private:
    enum CellState { EMPTY, OCCUPIED, DELETED };

    struct Cell {
        T value;
        CellState state = EMPTY;
    };

    std::vector<Cell> table;
    size_t capacity;
    size_t count = 0;
    float maxLoadFactor;
    int prime;
    int a, b;

    // Универсальная хеш-функция с параметрами
    size_t hash(const T& key, int a, int b) const {
        return ((a * std::hash<T>{}(key)+b) % prime) % capacity;
    }

    // Нахождение простого числа больше заданного
    int nextPrime(int n) const {
        if (n <= 1) return 2;
        while (true) {
            bool isPrime = true;
            for (int i = 2; i * i <= n; ++i) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return n;
            ++n;
        }
    }

    // Рехеширование таблицы
    void rehash() {
        size_t newCapacity = nextPrime(capacity * 2);
        std::vector<Cell> newTable(newCapacity);

        int newA = rand() % (prime - 1) + 1;
        int newB = rand() % prime;

        for (const auto& cell : table) {
            if (cell.state == OCCUPIED) {
                size_t idx = hash(cell.value, newA, newB);
                while (newTable[idx].state == OCCUPIED) {
                    idx = (idx + 1) % newCapacity;
                }
                newTable[idx] = cell;
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
        a = newA;
        b = newB;
    }

public:
    // Конструктор
    HashTableOpenAddressing(size_t initialCapacity = 11, float loadFactor = 0.75)
        : capacity(initialCapacity), maxLoadFactor(loadFactor) {
        if (initialCapacity < 1) throw std::invalid_argument("Capacity must be positive");
        if (loadFactor <= 0 || loadFactor >= 1) throw std::invalid_argument("Invalid load factor");

        prime = nextPrime(capacity);
        a = rand() % (prime - 1) + 1;
        b = rand() % prime;
        table.resize(capacity);
    }

    // Вставка элемента
    void insert(const T& key) {
        if (count >= maxLoadFactor * capacity) {
            rehash();
        }

        size_t idx = hash(key, a, b);
        size_t startIdx = idx;
        size_t firstDeleted = -1;

        // Поиск места для вставки
        do {
            if (table[idx].state == OCCUPIED && table[idx].value == key) {
                return; // Элемент уже существует
            }
            if (table[idx].state == DELETED && firstDeleted == -1) {
                firstDeleted = idx;
            }
            if (table[idx].state == EMPTY) {
                break;
            }
            idx = (idx + 1) % capacity;
        } while (idx != startIdx);

        // Вставка в найденное место
        if (firstDeleted != -1) {
            idx = firstDeleted;
        }
        table[idx].value = key;
        table[idx].state = OCCUPIED;
        ++count;
    }

    // Удаление элемента
    bool remove(const T& key) {
        size_t idx = hash(key, a, b);
        size_t startIdx = idx;

        do {
            if (table[idx].state == OCCUPIED && table[idx].value == key) {
                table[idx].state = DELETED;
                --count;
                return true;
            }
            if (table[idx].state == EMPTY) {
                break;
            }
            idx = (idx + 1) % capacity;
        } while (idx != startIdx);

        return false;
    }

    // Поиск элемента
    bool contains(const T& key) const {
        size_t idx = hash(key, a, b);
        size_t startIdx = idx;

        do {
            if (table[idx].state == OCCUPIED && table[idx].value == key) {
                return true;
            }
            if (table[idx].state == EMPTY) {
                break;
            }
            idx = (idx + 1) % capacity;
        } while (idx != startIdx);

        return false;
    }

    // Размер таблицы
    size_t size() const { return count; }
    bool empty() const { return count == 0; }

};
