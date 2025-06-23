#include "search.hpp"

#define d 256
const int MAX_CHAR = 256;

size_t searchRabinCarp(std::string pat, std::string txt, int q)
{
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one 
        if (p == t) {
            /* Check for characters one by one */
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    break;
                }
            }

            // if p == t and pat[0...M-1] = txt[i, i+1,
            // ...i+M-1]

            if (j == M)
                return i;
        }

        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // We might get negative value of t, converting
            // it to positive
            if (t < 0)
                t = (t + q);
        }
    }

    return std::string::npos;
}

size_t searchRabinCarp(std::string pat, std::string txt, int q, std::vector<size_t>& arr)
{
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    if (!arr.size()) {
        arr.clear();
    }
    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one 
        if (p == t) {
            /* Check for characters one by one */
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    break;
                }
            }

            // if p == t and pat[0...M-1] = txt[i, i+1,
            // ...i+M-1]

            if (j == M)
                arr.push_back(i);
        }

        // Calculate hash value for next window of text:
        // Remove leading digit, add trailing digit
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // We might get negative value of t, converting
            // it to positive
            if (t < 0)
                t = (t + q);
        }
    }

    return arr.size() ? arr[0] : std::string::npos;
}

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

void buildFiniteAutomaton(std::string pattern, int** TF) {
    int m = pattern.length();
    for (int i = 0; i < m+1; i++) {
        for (int j = 0; j < MAX_CHAR; j++) {
            TF[i][j] = 0;
        }
    }
    TF[0][(int) pattern[0]] = 1;
    int lps = 0;
    for (int i = 1; i < m+1; i++) {
        for (int j = 0; j < MAX_CHAR; j++) {
            TF[i][j] = TF[lps][j];
        }
        if (i < m) {
            TF[i][(int) pattern[i]] = i+1;
            lps = TF[lps][(int) pattern[i]];
        }
    }
}

size_t finiteAutomatonSearch(std::string text, std::string pattern) {
    int m = pattern.length();
    int n = text.length();
    int** TF = new int*[m+1];

    for (int i = 0; i < m+1; i++) {
        TF[i] = new int[MAX_CHAR];
    }

    buildFiniteAutomaton(pattern, TF);
    int i = 0;

    for (int j = 0; j < n; j++) {
        i = TF[i][(int) text[j]];
        if (i == m) {
            return j-m+1;
        }
    }

    for (int i = 0; i < m+1; i++) {
        delete[] TF[i];
    }
    delete[] TF;

    return std::string::npos;
}

size_t finiteAutomatonSearch(std::string text, std::string pattern, std::vector<size_t>& arr) {
    int m = pattern.length();
    int n = text.length();
    int** TF = new int*[m+1];

    if (!arr.size()) {
        arr.clear();
    }

    for (int i = 0; i < m+1; i++) {
        TF[i] = new int[MAX_CHAR];
    }

    buildFiniteAutomaton(pattern, TF);
    int i = 0;

    for (int j = 0; j < n; j++) {
        i = TF[i][(int) text[j]];
        if (i == m) {
            arr.push_back(j-m+1);
        }
    }

    for (int i = 0; i < m+1; i++) {
        delete[] TF[i];
    }
    delete[] TF;

    return arr.size() ? arr[0] : std::string::npos;
}

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
