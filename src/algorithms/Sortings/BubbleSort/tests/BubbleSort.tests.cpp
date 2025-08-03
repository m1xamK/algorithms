#include <gtest/gtest.h>
#include <vector>
#include <../include/BubbleSort.hpp>

TEST(BubbleSortTests, SortSingleElement)
{
    std::vector<int> vec = {42};
    BubbleSort::Sort(vec);
    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 42);
}

TEST(BubbleSortTests, SortAlreadySorted)
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::vector<int> expected = vec;
    BubbleSort::Sort(vec);
    EXPECT_EQ(vec, expected);
}

TEST(BubbleSortTests, SortReverseSorted)
{
    std::vector<int> vec = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    BubbleSort::Sort(vec);
    EXPECT_EQ(vec, expected);
}

TEST(BubbleSortTests, SortRandomOrder)
{
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    std::vector<int> expected = {1, 1, 2, 3, 4, 5, 6, 9};
    BubbleSort::Sort(vec);
    EXPECT_EQ(vec, expected);
}

TEST(BubbleSortTests, SortWithDuplicates)
{
    std::vector<int> vec = {2, 2, 1, 1, 3, 3};
    std::vector<int> expected = {1, 1, 2, 2, 3, 3};
    BubbleSort::Sort(vec);
    EXPECT_EQ(vec, expected);
}