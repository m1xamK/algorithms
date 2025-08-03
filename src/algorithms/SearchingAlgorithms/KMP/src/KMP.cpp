#include "../include/KMP.hpp"

namespace KMP {

    // Вычисление префикс-функции для паттерна
    std::vector<int> computePrefixFunction(const std::string& pattern) {
        int m = pattern.size();                // Длина паттерна
        std::vector<int> pi(m, 0);             // Префикс-функция: изначально нули
        int k = 0;                             // Текущая длина совпавшего префикса

        // Проходим по паттерну с 1 позиции (0 — всегда 0)
        for (int i = 1; i < m; ++i) {
            // Если символы не совпадают — сдвигаем префикс до предыдущего совпадения
            while (k > 0 && pattern[k] != pattern[i]) {
                k = pi[k - 1];
            }
            // Если символы совпадают — увеличиваем длину префикса
            if (pattern[k] == pattern[i]) {
                ++k;
            }
            // Записываем длину префикса в π-функцию для этой позиции
            pi[i] = k;
        }

        return pi;  // Возвращаем префикс-функцию
    }

    // Поиск всех вхождений паттерна в тексте
    std::vector<int> search(const std::string& text, const std::string& pattern) {
        int n = text.size();                   // Длина текста
        int m = pattern.size();                // Длина паттерна
        std::vector<int> pi = computePrefixFunction(pattern);  // Вычисляем π-функцию
        std::vector<int> result;               // Результат — индексы вхождений
        int q = 0;                             // Количество совпавших символов паттерна

        // Проходим по тексту
        for (int i = 0; i < n; ++i) {
            // Если символы не совпадают — "откатываемся" по π-функции
            while (q > 0 && pattern[q] != text[i]) {
                q = pi[q - 1];
            }
            // Если символы совпадают — двигаем указатель в паттерне
            if (pattern[q] == text[i]) {
                ++q;
            }
            // Если найдено полное совпадение паттерна
            if (q == m) {
                // Добавляем индекс начала совпадения в результат
                result.push_back(i - m + 1);
                // Продолжаем искать, используя префиксную информацию
                q = pi[q - 1];
            }
        }

        return result; // Возвращаем список индексов всех вхождений
    }

}
