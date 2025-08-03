#include "./KnutMorisPrattAlgo.hpp"

#define d 256
const int MAX_CHAR = 256;


void getPrefixTable(const std::string pattern, std::vector<int>& table) {
    const int len = pattern.size();
    int j = 0;
    for (int i = 1; i < len; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = table[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        table[i] = j;
    }
}

size_t searchKnuttMorisPratt(const std::string text, const std::string pattern) {
    const int n = text.size();
    const int m = pattern.size();
    std::vector<int> table(m);

    getPrefixTable(pattern, table);

    int j = 0;
    for (size_t i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = table[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i - m + 1;
        }
    }

    return std::string::npos;
}

size_t searchKnuttMorisPratt(const std::string text, const std::string pattern, std::vector<size_t>& arr) {
    const int n = text.size();
    const int m = pattern.size();
    std::vector<int> table(m);

    if (!arr.size()) {
        arr.clear();
    }

    getPrefixTable(pattern, table);

    int j = 0;
    for (size_t i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = table[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            arr.push_back(i - m + 1);
            j = table[j - 1];
        }
    }

    return arr.size() ? arr[0] : std::string::npos;
}