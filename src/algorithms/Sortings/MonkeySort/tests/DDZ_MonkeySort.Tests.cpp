#include "../include/DDZ_MonkeySort.h"
#include <gtest/gtest.h>
#include <vector>

TEST(MonkeySortTest, EmptyVector) {
    std::vector<int> arr;
    MonkeySort(arr);
    EXPECT_TRUE(arr.empty());
}

TEST(MonkeySortTest, SingleElement) {
    std::vector<int> arr = { 42 };
    MonkeySort(arr);
    EXPECT_EQ(arr, std::vector<int>({ 42 }));
}

TEST(MonkeySortTest, AlreadySorted) {
    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    MonkeySort(arr);
    EXPECT_EQ(arr, std::vector<int>({ 1, 2, 3, 4, 5 }));
}

TEST(MonkeySortTest, LargeUnsortedArray) {
    std::vector<int> arr = { 5, 3, 1, 9 };
    MonkeySort(arr);
    EXPECT_EQ(arr, std::vector<int>({ 1, 3, 5, 9 }));
}