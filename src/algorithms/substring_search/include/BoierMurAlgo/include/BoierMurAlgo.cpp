#include "./BoierMurAlgo.hpp"

#define d 256
const int MAX_CHAR = 256;


size_t searchBoierMur(std::string text, std::string pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) {
        badChar[pattern[i]] = i;
    }
    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }
        if (j < 0) {
            return shift;
        }
        shift += text[shift + j] <= 256 ? std::max(1, j - badChar[text[shift + j]]) : 1;
    }

    return std::string::npos;
}

size_t searchBoierMur(std::string text, std::string pattern, std::vector<size_t>& arr) {
    int N = text.length();
    int M = pattern.length();
    // Для хранения смещения каждого символа алфавита
    int badchar[256];

    if (!arr.size()) {
        arr.clear();
    }

    // Заполнение массива смещений букв в шаблоне
    for (int i = 0; i < 256; i++)
        badchar[i] = -1;

    for (int i = 0; i < M; i++)
        badchar[(int)pattern[i]] = i;

    // s - смещение шаблона относительно текста
    int s = 0;
    while (s <= (N - M))
    {
        int j = M - 1;

        // Поиск с конца шаблона до его начала
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0)
        {
            arr.push_back(s);
            s += (s + M < N) ? M - badchar[text[s + M]] : 1;
        }
        else
        {
            s += std::max(1, j - badchar[text[s + j]]);
        }
    }

    return arr.size() ? arr[0] : std::string::npos;
}
