#include <gtest/gtest.h>
#include <vector>
#include "../include/QSort/QSort.hpp"
#include <cstdlib>
#include <tuple>

#include <functional>
#include <fstream>
#define size 10000

typedef std::tuple<std::string, std::function<void(std::vector<int> &)>> test_data;

class SortParametrizedTest : public ::testing::TestWithParam<test_data> {
};

TEST_P(SortParametrizedTest, SortRandomTest) {
    auto[name, function] = GetParam();

    std::vector<int> arr(size);
    std::srand(time(NULL));
    for (size_t i = 0; i < size; ++i)
        arr[i] = std::rand();
    std::function<void(std::vector<int> &)> sort = function;
    auto begin = clock();
    sort(arr);
    auto end = clock();
    std::cout << "------------------------------------------" << std::endl;
    std::cout << name << " random value sort: " << (double) (end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST_P(SortParametrizedTest, SortOrderTest) {
    auto[name, function] = GetParam();

    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i)
        arr[i] = i;
    std::function<void(std::vector<int> &)> sort = function;
    auto begin = clock();
    sort(arr);
    auto end = clock();
    std::cout << "------------------------------------------" << std::endl;
    std::cout << name << " ordered value sort: " << (double) (end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST_P(SortParametrizedTest, SortUnOrderTest) {
    auto[name, function] = GetParam();

    std::vector<int> arr(size);
    for (int i = size - 1; i > -1; --i)
        arr[i] = i;
    std::function<void(std::vector<int> &)> sort = function;
    auto begin = clock();
    sort(arr);
    auto end = clock();
    std::cout << "------------------------------------------" << std::endl;
    std::cout << name << " unordered value sort: " << (double) (end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

TEST_P(SortParametrizedTest, SortDublicateTest) {
    auto[name, function] = GetParam();

    std::vector<int> arr(size);
    std::srand(time(NULL));
    for (size_t i = 0; i < size; ++i)
        arr[i] = std::rand() % 99;
    std::function<void(std::vector<int> &)> sort = function;
    auto begin = clock();
    sort(arr);
    auto end = clock();
    std::cout << "------------------------------------------" << std::endl;
    std::cout << name << " unordered value sort: " << (double) (end - begin) / CLOCKS_PER_SEC << "s" << std::endl;
    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
}

INSTANTIATE_TEST_SUITE_P(
        SortTest,
        SortParametrizedTest,
        ::testing::Values(
                std::make_tuple("QSort Test", quick_sort<int>)
        ));