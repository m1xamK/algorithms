#include <vector>
#include <random>
#include <stdexcept>
#include <functional>
#include <cmath>
#include <limits>
#include <iostream>

template<typename Key>
class PerfectHashTable {
private:
    struct SecondaryTable {
        std::vector<Key> table;
        int a = 0;
        int b = 0;
        size_t size = 0;
        Key emptyKey; // Специальное значение для пустых ячеек
    };

    std::vector<SecondaryTable> primaryTable;
    size_t primarySize;
    int primaryA;
    int primaryB;
    int prime;
    Key emptyKey; // Значение для пустых ячеек

    size_t universalHash(const Key& key, int a, int b, int m) const {
        size_t keyHash = std::hash<Key>{}(key);
        return ((a * keyHash + b) % prime) % m;
    }

    int findPrime(int n) const {
        if (n <= 1) return 2;
        int candidate = n;
        while (true) {
            bool isPrime = true;
            for (int i = 2; i * i <= candidate; ++i) {
                if (candidate % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return candidate;
            ++candidate;
        }
    }

    void initSecondaryTable(SecondaryTable& st, const std::vector<Key>& keys) {
        if (keys.empty()) {
            st.size = 0;
            return;
        }

        st.emptyKey = emptyKey;

        if (keys.size() == 1) {
            st.size = 1;
            st.table.resize(1);
            st.table[0] = keys[0];
            st.a = 0;
            st.b = 0;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disA(1, prime - 1);
        std::uniform_int_distribution<> disB(0, prime - 1);

        st.size = keys.size() * keys.size();
        bool collision;

        do {
            collision = false;
            st.a = disA(gen);
            st.b = disB(gen);
            st.table.assign(st.size, emptyKey);

            for (const Key& key : keys) {
                size_t pos = universalHash(key, st.a, st.b, st.size);
                if (st.table[pos] != emptyKey && st.table[pos] != key) {
                    collision = true;
                    break;
                }
                st.table[pos] = key;
            }
        } while (collision);
    }

public:
    PerfectHashTable(const std::vector<Key>& keys) {
        // Инициализируем специальное пустое значение
        emptyKey = std::numeric_limits<Key>::max();

        if (keys.empty()) {
            primarySize = 0;
            return;
        }

        prime = findPrime(keys.size());
        primarySize = keys.size();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disA(1, prime - 1);
        std::uniform_int_distribution<> disB(0, prime - 1);

        std::vector<std::vector<Key>> tempTable(primarySize);

        bool hasCollisions;
        do {
            hasCollisions = false;
            primaryA = disA(gen);
            primaryB = disB(gen);
            tempTable.assign(primarySize, std::vector<Key>());

            for (const Key& key : keys) {
                size_t pos = universalHash(key, primaryA, primaryB, primarySize);
                tempTable[pos].push_back(key);
            }

            size_t sumSquares = 0;
            for (const auto& bucket : tempTable) {
                sumSquares += bucket.size() * bucket.size();
            }
            if (sumSquares > 4 * keys.size()) {
                hasCollisions = true;
            }
        } while (hasCollisions);

        primaryTable.resize(primarySize);
        for (size_t i = 0; i < primarySize; ++i) {
            initSecondaryTable(primaryTable[i], tempTable[i]);
        }
    }

    bool contains(const Key& key) const {
        if (primarySize == 0) return false;

        size_t primaryPos = universalHash(key, primaryA, primaryB, primarySize);
        const SecondaryTable& st = primaryTable[primaryPos];

        if (st.size == 0) return false;

        size_t secondaryPos = universalHash(key, st.a, st.b, st.size);
        return st.table[secondaryPos] == key && st.table[secondaryPos] != emptyKey;
    }

    void printStats() const {
        std::cout << "Primary table size: " << primarySize << "\n";
        std::cout << "Primary hash params: a=" << primaryA << ", b=" << primaryB << "\n";
        std::cout << "Prime number: " << prime << "\n";

        for (size_t i = 0; i < primarySize; ++i) {
            const auto& st = primaryTable[i];
            std::cout << "Bucket " << i << ": size=" << st.size;
            std::cout << ", hash params: a=" << st.a << ", b=" << st.b << "\n";
        }
    }
};