#include "../BST/bst.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

TEST(BinaryTreeTests, EmptyTreeTest)
{
	BinaryTree<int> tree;
	EXPECT_TRUE(tree.Empty());
}

TEST(BinaryTreeTests, InsertElemTest)
{
	BinaryTree<int> tree;
	tree.Insert(2);
	EXPECT_FALSE(tree.Empty());
}

TEST(BinaryTreeTests, InsertSomeElemTest)
{
	BinaryTree<int> tree;
	tree.Insert(10);
	tree.Insert(7);
	tree.Insert(14);
	tree.Insert(12);
	tree.Insert(9);
	tree.Insert(2);
	tree.Insert(11);
	tree.Insert(20);
	EXPECT_FALSE(tree.Empty());
}

TEST(BinaryTreeTests, InsertElemFromArrTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree(arr);
	EXPECT_FALSE(tree.Empty());
}

TEST(BinaryTreeTests, InsertExistElemTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree(arr);
	EXPECT_FALSE(tree.Insert(12));
}

TEST(BinaryTreeTests, IsElementExistTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree(arr);
	EXPECT_TRUE(tree.Contains(14));
	EXPECT_TRUE(tree.Contains(11));
}

TEST(BinaryTreeTests, IsElementNotExistTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree(arr);
	EXPECT_FALSE(tree.Contains(333));
	EXPECT_FALSE(tree.Contains(144));
}

TEST(BinaryTreeTests, TakeArrFromTreeTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	vector<int> resArr{ 10, 2, 7, 9, 10, 11, 12, 14, 20 };
	BinaryTree<int> tree(arr);
	EXPECT_EQ(resArr, tree.ToVector());
}

TEST(BinaryTreeTests, CopyConstructorTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree1(arr);
	BinaryTree<int> tree2(tree1);

	EXPECT_FALSE(tree1.Empty());
	EXPECT_FALSE(tree1.Contains(333));
	EXPECT_FALSE(tree1.Contains(144));
	EXPECT_TRUE(tree1.Contains(14));
	EXPECT_TRUE(tree1.Contains(11));

	EXPECT_FALSE(tree2.Empty());
	EXPECT_FALSE(tree2.Contains(333));
	EXPECT_FALSE(tree2.Contains(144));
	EXPECT_TRUE(tree2.Contains(14));
	EXPECT_TRUE(tree2.Contains(11));
}

TEST(BinaryTreeTests, MovementsConstructorTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree1(arr);
	BinaryTree<int> tree2 = move(tree1);
	EXPECT_TRUE(tree1.Empty());
	EXPECT_FALSE(tree2.Empty());
	EXPECT_FALSE(tree2.Contains(333));
	EXPECT_FALSE(tree2.Contains(144));
	EXPECT_TRUE(tree2.Contains(14));
	EXPECT_TRUE(tree2.Contains(11));
}

TEST(BinaryTreeTests, RightPartOfTreeTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20,22,19,17,13 };
	vector<int> resArr{11,12,13,14,17,19,20,22};
	BinaryTree<int> tree(arr);
	EXPECT_EQ(resArr, tree.RoundLrootR());
}

TEST(BinaryTreeTests, LeftPartOfTreeTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20,3,4,1};
	vector<int> resArr{1,2,3,4,7,9};
	BinaryTree<int> tree(arr);
	EXPECT_EQ(resArr, tree.RoundRrootL());
}

TEST(BinaryTreeTests, RemoveElemNoChildTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree(arr);
	EXPECT_TRUE(tree.Remove(2));
	EXPECT_FALSE(tree.Contains(2));
}

TEST(BinaryTreeTests, RemoveNoSuchElemTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree(arr);
	EXPECT_FALSE(tree.Remove(111));
}

TEST(BinaryTreeTests, RemoveElemLeftChildTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree(arr);
	EXPECT_TRUE(tree.Remove(12));
	EXPECT_FALSE(tree.Contains(12));
}

TEST(BinaryTreeTests, RemoveElemRightChildTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20,27 };
	BinaryTree<int> tree(arr);
	EXPECT_TRUE(tree.Remove(20));
	EXPECT_FALSE(tree.Contains(20));
}

TEST(BinaryTreeTests, RemoveElemChildren1Test)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20 };
	BinaryTree<int> tree(arr);
	EXPECT_TRUE(tree.Remove(10));
	EXPECT_FALSE(tree.Contains(10));
}

TEST(BinaryTreeTests, RemoveElemChildren2Test)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20,22,19,17,13 };
	BinaryTree<int> tree(arr);
	EXPECT_TRUE(tree.Remove(14));
	EXPECT_FALSE(tree.Contains(14));
}

TEST(BinaryTreeTests, PrintBTTest)
{
	vector<int> arr{ 10,7,14,12,9,2,11,20,13,4,21,8,19,1 };
	BinaryTree<int> tree(arr);
	tree.Print();
}

