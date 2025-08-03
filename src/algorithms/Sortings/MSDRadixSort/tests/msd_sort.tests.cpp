// msd_sort_test.cpp
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
#include "../include/msd_sort.h"

TEST(MsdSortTest, EmptyVector) {
    std::vector<int> v;
    msd::msd_radix_sort(v.begin(), v.end());
    EXPECT_TRUE(v.empty());
}

TEST(MsdSortTest, SingleElement) {
    std::vector<int> v = {42};
    msd::msd_radix_sort(v.begin(), v.end());
    ASSERT_EQ(v.size(), 1);
    EXPECT_EQ(v[0], 42);
}

TEST(MsdSortTest, AlreadySorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    msd::msd_radix_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(MsdSortTest, ReverseSorted) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    msd::msd_radix_sort(v.begin(), v.end());
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}


TEST(MsdSortTest, NegativeNumbers) 
{
    std::vector<int> v = {-5, 3, -2, 0, 7, -1, 4};
    std::vector<int> expected = { 0, 3, 4, 7, -5, -2, -1 };
    
    msd::msd_radix_sort(v.begin(), v.end());
    EXPECT_EQ(v, expected);
}


//#TODO: Добавить тест хотя бы для 1000 элементов (положите в вектор рандомное число от 0 до 10 и отсортируйте такой вектор
TEST(MsdSortTest, Random100Elements) {
    std::vector<int> v(100);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
    
    for (auto& num : v) {
        num = dist(gen);
    }
    
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    
    msd::msd_radix_sort(v.begin(), v.end());
    
    EXPECT_EQ(v.size(), expected.size());
}

TEST(MsdSortTest, Random1000Elements) {
    std::vector<int> v(1000);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(INT_MIN/2, INT_MAX/2); // Уменьшенный диапазон
    
    for (auto& num : v) {
        num = dist(gen);
    }
    
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    
    msd::msd_radix_sort(v.begin(), v.end());
    
    EXPECT_EQ(v.size(), expected.size());
}

TEST(MsdSortTest, Random10000Elements) {
    std::vector<int> v(10000);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-10000, 10000); // Еще меньший диапазон
    
    for (auto& num : v) {
        num = dist(gen);
    }
    
    std::vector<int> expected = v;
    std::sort(expected.begin(), expected.end());
    
    msd::msd_radix_sort(v.begin(), v.end());
    
    EXPECT_EQ(v.size(), expected.size());
}