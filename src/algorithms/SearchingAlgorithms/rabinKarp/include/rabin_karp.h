#include <string>
#include <vector>
using namespace std;

const int BASE = 256; // Основание для хеширования (число возможных символов)
const int PRIME = 101; // Простое число для модуляции хешей

/**
 * @brief Выполняет поиск всех вхождений подстроки (pattern) в строку (text) с помощью алгоритма Рабина-Карпа.
 * 
 * Алгоритм Рабина-Карпа использует хеширование для эффективного поиска подстроки.
 * Хеши сравниваются, и при совпадении выполняется посимвольное сравнение для проверки.
 * 
 * @param text Основной текст, в котором выполняется поиск.
 * @param pattern Подстрока, которую необходимо найти.
 * @return std::vector<int> Вектор индексов начала каждого вхождения pattern в text.
 *                         Если вхождений нет, возвращается пустой вектор.
 */
vector<int> rabin_karp_search(const string& text, const string& pattern) {
    vector<int> matches;
    int n = text.length();
    int m = pattern.length();

    if (n < m || m == 0) return matches;

    // Вычисляем значение BASE^(m-1) по модулю PRIME для использования при скользящем хеше
    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * BASE) % PRIME;
    }

    // Вычисляем начальные хеши для образца и первого окна текста
    int pattern_hash = 0;
    int window_hash = 0;
    for (int i = 0; i < m; i++) {
        pattern_hash = (BASE * pattern_hash + pattern[i]) % PRIME;
        window_hash = (BASE * window_hash + text[i]) % PRIME;
    }

    // Проходим по тексту и сравниваем хеши
    for (int i = 0; i <= n - m; i++) {
        // Если хеши совпали, проверяем символы для подтверждения совпадения
        if (pattern_hash == window_hash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                matches.push_back(i);
            }
        }

        // Вычисляем хеш следующего окна текста (если оно существует)
        if (i < n - m) {
            window_hash = (BASE * (window_hash - text[i] * h) + text[i + m]) % PRIME;

            // Корректируем отрицательный хеш
            if (window_hash < 0) {
                window_hash += PRIME;
            }
        }
    }

    return matches;
}