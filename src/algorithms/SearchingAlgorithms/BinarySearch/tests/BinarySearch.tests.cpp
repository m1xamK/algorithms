#include <gtest/gtest.h>
#include <vector>
#include "../include/BinarySearchRecursive.h"
#include "../include/BinarySearchIterative.h"

// Тесты для рекурсивной реализации
TEST(BinarySearchRecursiveTest, FindsElementInMiddle) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    EXPECT_EQ(binarySearchRecursive(arr, 0, arr.size()-1, 7), 3);
}

TEST(BinarySearchRecursiveTest, FindsElementAtBeginning) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    EXPECT_EQ(binarySearchRecursive(arr, 0, arr.size()-1, 1), 0);
}

TEST(BinarySearchRecursiveTest, FindsElementAtEnd) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    EXPECT_EQ(binarySearchRecursive(arr, 0, arr.size()-1, 15), 7);
}

TEST(BinarySearchRecursiveTest, ReturnsNotFound) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    EXPECT_EQ(binarySearchRecursive(arr, 0, arr.size()-1, 2), -1);
}

TEST(BinarySearchRecursiveTest, HandlesEmptyArray) {
    std::vector<int> empty;
    EXPECT_EQ(binarySearchRecursive(empty, 0, empty.size()-1, 1), -1);
}

TEST(BinarySearchRecursiveTest, HandlesSingleElement) {
    std::vector<int> single = {5};
    EXPECT_EQ(binarySearchRecursive(single, 0, single.size()-1, 5), 0);
    EXPECT_EQ(binarySearchRecursive(single, 0, single.size()-1, 3), -1);
}

// Тесты для итеративной реализации
TEST(BinarySearchIterativeTest, FindsElementInMiddle) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    EXPECT_EQ(binarySearchIterative(arr, 7), 3);
}

TEST(BinarySearchIterativeTest, FindsElementAtBeginning) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    EXPECT_EQ(binarySearchIterative(arr, 1), 0);
}

TEST(BinarySearchIterativeTest, FindsElementAtEnd) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    EXPECT_EQ(binarySearchIterative(arr, 15), 7);
}

TEST(BinarySearchIterativeTest, ReturnsNotFound) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    EXPECT_EQ(binarySearchIterative(arr, 2), -1);
}

TEST(BinarySearchIterativeTest, HandlesEmptyArray) {
    std::vector<int> empty;
    EXPECT_EQ(binarySearchIterative(empty, 1), -1);
}

TEST(BinarySearchIterativeTest, HandlesSingleElement) {
    std::vector<int> single = {5};
    EXPECT_EQ(binarySearchIterative(single, 5), 0);
    EXPECT_EQ(binarySearchIterative(single, 3), -1);
}

TEST(BinarySearchTypesTest, WorksWithDoubles) {
    std::vector<double> arr = {1.1, 2.2, 3.3, 4.4, 5.5};
    EXPECT_EQ(binarySearchIterative(arr, 3.3), 2);
    EXPECT_EQ(binarySearchRecursive(arr, 0, arr.size()-1, 4.4), 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}