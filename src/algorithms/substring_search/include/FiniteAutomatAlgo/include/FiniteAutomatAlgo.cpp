#include "./FiniteAutomatAlgo.hpp"

#define d 256
const int MAX_CHAR = 256;


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