#include "../include/rabin_karp.h"
#include <iostream>
#include <vector>
#include <cstdlib>  // для rand, srand
#include <ctime>    // для time
#include <gtest/gtest.h>

// Тесты с использованием Google Test
TEST(RabinKarpTest, BasicSearch) {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    vector<int> expected = { 10 };
    EXPECT_EQ(rabin_karp_search(text, pattern), expected);
}

TEST(RabinKarpTest, PatternAtEnd) {
    string text = "hello world";
    string pattern = "world";
    vector<int> expected = { 6 };
    EXPECT_EQ(rabin_karp_search(text, pattern), expected);
}

TEST(RabinKarpTest, MultipleMatches) {
    string text = "aaaaa";
    string pattern = "aa";
    vector<int> expected = { 0, 1, 2, 3 };
    EXPECT_EQ(rabin_karp_search(text, pattern), expected);
}

TEST(RabinKarpTest, NoMatches) {
    string text = "abcde";
    string pattern = "xyz";
    vector<int> expected = {};
    EXPECT_EQ(rabin_karp_search(text, pattern), expected);
}

TEST(RabinKarpTest, EmptyPattern) {
    string text = "a";
    string pattern = "";
    vector<int> expected = {};
    EXPECT_EQ(rabin_karp_search(text, pattern), expected);
}

TEST(RabinKarpTest, EmptyText) {
    string text = "";
    string pattern = "a";
    vector<int> expected = {};
    EXPECT_EQ(rabin_karp_search(text, pattern), expected);
}

TEST(RabinKarpTest, OverlappingMatches) {
    string text = "mississippi";
    string pattern = "issi";
    vector<int> expected = { 1, 4 };
    EXPECT_EQ(rabin_karp_search(text, pattern), expected);
}

// Новый тест: поиск в случайной строке
TEST(RabinKarpTest, RandomString) {
    srand(static_cast<unsigned int>(time(nullptr)));

    const int text_length = 1000;
    const int pattern_length = 5;

    string text;
    for (int i = 0; i < text_length; ++i) {
        text += static_cast<char>('a' + rand() % 26);
    }

    string pattern;
    for (int i = 0; i < pattern_length; ++i) {
        pattern += static_cast<char>('a' + rand() % 26);
    }

    // Проверяем, что все найденные вхождения действительно совпадают с паттерном
    vector<int> matches = rabin_karp_search(text, pattern);
    for (int pos : matches) {
        EXPECT_EQ(text.substr(pos, pattern_length), pattern);
    }
}

// Новый тест: поиск в очень длинной строке
TEST(RabinKarpTest, VeryLongString) {
    // Создаем строку из миллиона символов 'a'
    const int text_length = 1'000'000;
    string text(text_length, 'a');

    // Паттерн "aaaaa"
    string pattern = "aaaaa";

    // Ожидаем все позиции с 0 по text_length - pattern_length
    vector<int> expected;
    for (int i = 0; i <= text_length - (int)pattern.length(); ++i) {
        expected.push_back(i);
    }

    vector<int> result = rabin_karp_search(text, pattern);
    EXPECT_EQ(result.size(), expected.size());
    // Дополнительно проверим первые и последние несколько индексов для экономии времени
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(result[i], expected[i]);
        EXPECT_EQ(result[result.size() - 1 - i], expected[expected.size() - 1 - i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
