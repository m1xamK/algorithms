#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <iostream>

template<typename Key>
class HashTableChaining {
private:
    std::vector<std::list<Key>> table;  
    size_t capacity;                    
    size_t count = 0;                   
    float maxLoadFactor;                

    // Основная хеш-функция
    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % capacity;
    }

    // Рехеширование таблицы при превышении коэффициента загрузки
    void rehash() {
        size_t newCapacity = capacity * 2;
        std::vector<std::list<Key>> newTable(newCapacity);

        for (auto& chain : table) {
            for (const Key& key : chain) {
                size_t newHash = std::hash<Key>{}(key) % newCapacity;
                newTable[newHash].push_front(key);
            }
        }

        table = std::move(newTable);
        capacity = newCapacity;
    }

public:
    // Конструктор с параметрами по умолчанию
    HashTableChaining(size_t initialCapacity = 11, float loadFactor = 0.75)
        : capacity(initialCapacity), maxLoadFactor(loadFactor) {
        if (initialCapacity < 1) throw std::invalid_argument("Capacity must be positive");
        if (loadFactor <= 0) throw std::invalid_argument("Load factor must be positive");
        table.resize(capacity);
    }

    // Вставка элемента (дубликаты не допускаются)
    void insert(const Key& key) {
        if (loadFactor() > maxLoadFactor) {
            rehash();
        }

        size_t idx = hash(key);
        for (const Key& k : table[idx]) {
            if (k == key) return;  // Элемент уже существует
        }

        table[idx].push_front(key);
        ++count;
    }

    // Удаление элемента
    bool remove(const Key& key) {
        size_t idx = hash(key);
        auto& chain = table[idx];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (*it == key) {
                chain.erase(it);
                --count;
                return true;
            }
        }
        return false;
    }

    // Проверка наличия элемента
    bool contains(const Key& key) const {
        size_t idx = hash(key);
        for (const Key& k : table[idx]) {
            if (k == key) return true;
        }
        return false;
    }

    // Текущий коэффициент загрузки
    float loadFactor() const {
        return static_cast<float>(count) / capacity;
    }

    // Количество элементов
    size_t size() const { return count; }

    // Проверка на пустоту
    bool empty() const { return count == 0; }

    // Вывод содержимого таблицы (для отладки)
    void print() const {
        for (size_t i = 0; i < capacity; ++i) {
            std::cout << "[" << i << "]: ";
            for (const Key& key : table[i]) {
                std::cout << key << " -> ";
            }
            std::cout << "null\n";
        }
    }
};