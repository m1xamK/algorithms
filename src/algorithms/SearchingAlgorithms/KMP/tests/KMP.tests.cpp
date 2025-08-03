#include "../include/KMP.hpp"
#include <cassert>
#include <iostream>
#include <gtest/gtest.h>

TEST(KMPTest, NoMatch) {
    std::string text = "abcdefgh";
    std::string pattern = "xyz";

    auto result = KMP::search(text, pattern);

    ASSERT_TRUE(result.empty());  // Нет совпадений
}

TEST(KMPTest, SingleMatch) {
    std::string text = "abcdefgh";
    std::string pattern = "cde";

    auto result = KMP::search(text, pattern);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 2);
}

TEST(KMPTest, FullMatch) {
    std::string text = "abcabc";
    std::string pattern = "abcabc";

    auto result = KMP::search(text, pattern);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}

TEST(KMPTest, OverlappingMatches) {
    std::string text = "aaaaa";
    std::string pattern = "aaa";

    auto result = KMP::search(text, pattern);

    ASSERT_EQ(result.size(), 3);  // "aaa" найдено в индексах 0, 1, 2
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 2);
}

TEST(KMPTest, PatternLongerThanText) {
    std::string text = "abc";
    std::string pattern = "abcd";

    auto result = KMP::search(text, pattern);

    ASSERT_TRUE(result.empty());  // Невозможно найти паттерн
}
