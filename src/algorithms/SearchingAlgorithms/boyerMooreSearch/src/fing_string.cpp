#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>

class FindString {
public:
    FindString() {}

    // Эвристика плохого символа
    std::unordered_map<char, int> makeImage(std::string substr) {
        std::unordered_map<char, int> map;
        const int substr_size = substr.size() - 1;
        if (substr_size == -1) {
            throw std::runtime_error("Error! Wrong substring!");
        }
        for (int i = substr_size - 1; i >= 0; --i) {
            map.try_emplace(substr[i], substr_size - i);
        }
        map.try_emplace(substr[substr_size], substr_size + 1);
        return map;
    }

    // Функция для эвристики хорошего суффикса
    std::vector<int> makeGoodSuffixTable(const std::string& pattern) {
        int m = pattern.size();
        std::vector<int> goodSuffixShift(m + 1, m);
        std::vector<int> borderPos(m + 1, 0);

        // Этап 1: Находим границы
        int i = m, j = m + 1;
        borderPos[i] = j;
        while (i > 0) {
            while (j <= m && pattern[i-1] != pattern[j-1]) {
                if (goodSuffixShift[j] == m) {
                    goodSuffixShift[j] = j - i;
                }
                j = borderPos[j];
            }
            i--; j--;
            borderPos[i] = j;
        }

        // Этап 2: Устанавливаем сдвиги для префиксов
        j = borderPos[0];
        for (i = 0; i <= m; i++) {
            if (goodSuffixShift[i] == m) {
                goodSuffixShift[i] = j;
            }
            if (i == j) {
                j = borderPos[j];
            }
        }

        return goodSuffixShift;
    }

    // Функция поиска с двумя эвристиками
    bool boyerMooreSearch(std::string substr, std::string str) {
        auto badCharTable = makeImage(substr);
        auto goodSuffixTable = makeGoodSuffixTable(substr);
        
        int str_size = str.size();
        int substr_size = substr.size();
        
        if (substr_size == 0) {
            return true;
        }
        if (substr_size > str_size) {
            return false;
        }

        int i = 0; // текущая позиция в тексте
        while (i <= str_size - substr_size) {
            int j = substr_size - 1;
            
            // Сравнение справа налево
            while (j >= 0 && substr[j] == str[i + j]) {
                j--;
            }

            if (j < 0) {
                return true;
            } else {
                // Вычисляем сдвиг по плохому символу
                int badCharShift = badCharTable.count(str[i + j]) ? 
                                 badCharTable[str[i + j]] : substr_size + 1;
                
                // Вычисляем сдвиг по хорошему суффиксу
                int goodSuffixShift = goodSuffixTable[j + 1];
                
                // Выбираем максимальный сдвиг
                i += std::max(badCharShift, goodSuffixShift);
            }
        }
        return false;
    }
};