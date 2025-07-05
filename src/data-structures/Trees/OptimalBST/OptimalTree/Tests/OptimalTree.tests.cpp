#include "../OptimalTree.h"
#include "pch.h"

TEST(SearchTest, NonExistentElementTest)
{
    vector<int> keys = {1, 6, 8, 10};
    vector<double> p = {0.11, 0.09, 0.02, 0.16};
    vector<double> q = {0.07, 0.18, 0.04, 0.2, 0.13};
    OptimalBinaryTree<int> tree(keys, p, q);
    ASSERT_TRUE(tree.Search(1000) == 0);
    ASSERT_TRUE(tree.Search(6660) == 0);
    ASSERT_TRUE(tree.Search(10121) == 0);
    ASSERT_TRUE(tree.Search(8345345) == 0);
    ASSERT_TRUE(tree.Search(100) == 0);
}
TEST(SearchTest, EmptyTreeTest)
{
    vector<int> keys = {0};
    vector<double> p = {0};
    vector<double> q = {0};
    OptimalBinaryTree<int> tree(keys, p, q);
    ASSERT_TRUE(tree.Search(1000) == 0);
    ASSERT_TRUE(tree.Search(6660) == 0);
    ASSERT_TRUE(tree.Search(10121) == 0);
    ASSERT_TRUE(tree.Search(8345345) == 0);
    ASSERT_TRUE(tree.Search(100) == 0);
}

TEST(SearchTest, CorrectElemSearchTest)
{
    vector<int> keys = {1, 6, 8, 10};
    vector<double> p = {0.11, 0.09, 0.02, 0.16};
    vector<double> q = {0.07, 0.18, 0.04, 0.2, 0.13};
    OptimalBinaryTree<int> tree(keys, p, q);
    ASSERT_TRUE(tree.Search(1) == 1);
    ASSERT_TRUE(tree.Search(6) == 6);
    ASSERT_TRUE(tree.Search(10) == 10);
    ASSERT_TRUE(tree.Search(8) == 8);
    ASSERT_TRUE(tree.Search(100) == 0);
}

TEST(DetourTest, LRDetourTest)
{
    vector<int> keys = {1, 6, 8, 10};
    vector<double> p = {0.11, 0.09, 0.02, 0.16};
    vector<double> q = {0.07, 0.18, 0.04, 0.2, 0.13};
    OptimalBinaryTree<int> tree(keys, p, q);
    ASSERT_TRUE(tree.RoundLrootR() == keys);
}

TEST(DetourTest, RLDetourTest)
{
    vector<int> keys = {1, 6, 8, 10};
    vector<double> p = {0.11, 0.09, 0.02, 0.16};
    vector<double> q = {0.07, 0.18, 0.04, 0.2, 0.13};
    OptimalBinaryTree<int> tree(keys, p, q);
    std::reverse(keys.begin(), keys.end());
    ASSERT_TRUE(tree.RoundRrootL() == keys);
}

TEST(Output, RightOutputTest)
{
    vector<int> keys = {1, 6, 8, 10, 20, 25, 48, 88};
    vector<double> p = {0.03, 0.02, 0.05, 0.10, 0.04, 0.15, 0.08, 0.09};
    vector<double> q = {0.07, 0.03, 0.05, 0.01, 0.02, 0.04, 0.08, 0.09, 0.06};
    OptimalBinaryTree<int> tree(keys, p, q);
    tree.Output();
}