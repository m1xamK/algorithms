#include <gtest/gtest.h>
#include "../include/AVLTree/AVLTree.hpp"
#include <filesystem>

TEST(ConstructorTests, DefaultConstructorTest)
{
    AVLTree<int> tree = AVLTree<int>();
    EXPECT_TRUE(tree.Empty());
}

TEST(InsertTests, MainTest)
{
    AVLTree<int> tree = AVLTree<int>();
    tree.Insert(10);
    EXPECT_EQ(tree.GetRoot()->_value, 10);
    tree.Insert(47);
    EXPECT_EQ(tree.GetRoot()->_right->_value, 47);
    tree.Insert(4);
    EXPECT_EQ(tree.GetRoot()->_left->_value, 4);
}

TEST(ConstructorTests, ConstructorWithParametersTest)
{
    int* arr = new int[5] {10, 47, 65, 99, 82};
    int n = 5;
    AVLTree<int> tree = AVLTree<int>(arr, n);
    EXPECT_TRUE(!tree.Empty());
    EXPECT_EQ(tree.GetRoot()->_value, 47);
}

TEST(RemoveTests, RemoveSheet)
{
    int* arr = new int[7] {10, 47, 65, 99, 82, 4, 61};
    AVLTree<int> tree = AVLTree<int>(arr, 7);
    EXPECT_TRUE(tree.Remove(61));
}

TEST(RemoveTests, RemoveWithOneDescendent)
{
    int* arr = new int[7] {10, 47, 65, 99, 82, 4, 61};
    AVLTree<int> tree = AVLTree<int>(arr, 7);
    EXPECT_TRUE(tree.Remove(65));
}

TEST(RemoveTests, RemoveWithTwoDescendents)
{
    int* arr = new int[7] {10, 47, 65, 99, 82, 4, 61};
    AVLTree<int> tree = AVLTree<int>(arr, 7);
    EXPECT_TRUE(tree.Remove(47));
    EXPECT_EQ(tree.GetRoot()->_value, 65);
}

TEST(RemoveTests, RemoveElementNotInTree)
{
    int* arr = new int[7] {10, 47, 65, 99, 82, 4, 61};
    AVLTree<int> tree = AVLTree<int>(arr, 7);
    EXPECT_FALSE(tree.Remove(57));
}

TEST(FindTests, NotFind)
{
    int* arr = new int[7] {10, 47, 65, 99, 82, 4, 61};
    AVLTree<int> tree = AVLTree<int>(arr, 7);
    EXPECT_FALSE(tree.Find(57));
}

TEST(FindTests, FindElementByValue)
{
    int* arr = new int[7] {10, 47, 65, 99, 82, 4, 61};
    AVLTree<int> tree = AVLTree<int>(arr, 7);
    EXPECT_TRUE(tree.Find(82));
}

TEST(WalkTests, MainTest)
{
    int* arr = new int[7] {10, 47, 65, 99, 82, 4, 61};
    AVLTree<int> tree = AVLTree<int>(arr, 7);   
    std::vector<int> result = tree.Walk();
    std::vector<int> should_res = {47, 10, 4, 82, 65, 61, 99};
    EXPECT_EQ(should_res, result); 
}

TEST(OutputTests, MainTest)
{
    int* arr = new int[5] {10, 47, 65, 99, 82};
    AVLTree<int> tree = AVLTree<int>(arr, 5);
    tree.Insert(4);
    tree.Insert(61);
    EXPECT_TRUE(tree.Remove(47));
    tree.Output();
    tree.MakeGVFile("graph1.gv");
    char* command = "dot graph1.gv | gvpr -c -ftree.gv | neato -n -Tpng -o graph1.png";
    std::system(command);
}