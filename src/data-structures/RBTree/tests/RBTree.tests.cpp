#include <gtest/gtest.h>
#include <vector>
#include <filesystem>
#include <RBTree/RBTree.hpp>

TEST(RBTreeTests, EmptyTreeTests)
{
    RBTree<int> tree;
    EXPECT_TRUE(tree.empty());
}

TEST(RBTreeTests, AddingElementsTests)
{
    RBTree<int> tree;
    std::vector<int> vec = {1, 6, 13, 8, 15, 17, 22, 25, 27, 11};
    auto test_name = std::string(::testing::UnitTest::GetInstance()->current_test_info()->name());
    auto path = test_name + "Img/";
    std::filesystem::create_directory(path);
    for (auto i : vec)
    {
        tree.insert(i);
        EXPECT_TRUE(tree.contains(i));
        tree.MakeGVFile(path + test_name + "_" + std::to_string(i) + ".gv");
        auto command = "dot " + path + test_name + "_" + std::to_string(i) +
                       ".gv | gvpr -c -f../../../RBTree/rbtree.gv | neato -n -Tpng -o " +
                       path + test_name + "_" + std::to_string(i) + ".png";
        std::system(command.c_str());
        auto command_delete = "rm " + path + test_name + "_" + std::to_string(i) + ".gv";
        std::system(command_delete.c_str());
    }
}

TEST(RBTreeTests, TreeFromVectorTests)
{
    std::vector<int> vec = {1, 0, 100, 15, 16, 42, 254, 37, 86, 72, 43};
    RBTree<int> tree(vec);

    for (auto i : vec)
    {
        EXPECT_TRUE(tree.contains(i));
    }
    auto test_name = std::string(::testing::UnitTest::GetInstance()->current_test_info()->name());
    auto path = test_name + "Img/";
    std::filesystem::create_directory(path);
    tree.MakeGVFile(path + test_name + "_.gv");
    auto command = "dot " + path + test_name + "_" +
                   ".gv | gvpr -c -f../../../RBTree/rbtree.gv | neato -n -Tpng -o " +
                   path + test_name + "_.png";
    std::system(command.c_str());
    auto command_delete = "rm " + path + test_name + "_.gv";
    std::system(command_delete.c_str());
}

TEST(RBTreeTests, RemovingElementsTests)
{
    std::vector<int> vec = {10, 20, 9, 6, 8, 1, 100};
    RBTree<int> tree(vec);
    auto test_name = std::string(::testing::UnitTest::GetInstance()->current_test_info()->name());
    auto path = test_name + "Img/";
    std::filesystem::create_directory(path);
    for (auto i : vec)
    {
        EXPECT_TRUE(tree.contains(i));
    }

    tree.remove(1);

    tree.MakeGVFile(path + test_name + "_" + "1" + ".gv");
    auto command = "dot " + path + test_name + "_" + "1" +
                   ".gv | gvpr -c -f../../../RBTree/rbtree.gv | neato -n -Tpng -o " +
                   path + test_name + "_" + "1" + ".png";
    std::system(command.c_str());
    auto command_delete = "rm " + path + test_name + "_" + "1" + ".gv";
    std::system(command_delete.c_str());

    EXPECT_FALSE(tree.contains(1));
    for (auto i : vec)
    {
        EXPECT_TRUE(tree.contains(i) || i == 1);
    }

    tree.remove(20);

    tree.MakeGVFile(path + test_name + "_" + "20" + ".gv");
    command = "dot " + path + test_name + "_" + "20" +
              ".gv | gvpr -c -f../../../RBTree/rbtree.gv | neato -n -Tpng -o " +
              path + test_name + "_" + "20" + ".png";
    std::system(command.c_str());
    command_delete = "rm " + path + test_name + "_" + "20" + ".gv";
    std::system(command_delete.c_str());

    EXPECT_FALSE(tree.contains(20));
    for (auto i : vec)
    {
        EXPECT_TRUE(tree.contains(i) || i == 1 || i == 20);
    }

    tree.remove(6);

    EXPECT_FALSE(tree.contains(6));
    for (auto i : vec)
    {
        EXPECT_TRUE(tree.contains(i) || i == 1 || i == 20 || i == 6);
    }

    tree.MakeGVFile(path + test_name + "_" + "6" + ".gv");
    command = "dot " + path + test_name + "_" + "6" +
              ".gv | gvpr -c -f../../../RBTree/rbtree.gv | neato -n -Tpng -o " +
              path + test_name + "_" + "6" + ".png";
    std::system(command.c_str());
    command_delete = "rm " + path + test_name + "_" + "6" + ".gv";
    std::system(command_delete.c_str());
}

TEST(RBTreeTests, WalkingTreeTests)
{
    std::vector<int> vec = {10, 20, 9, 6, 8, 1, 100};
    RBTree<int> tree(vec);
    std::vector<int> ans = {1, 6, 8, 9, 10, 20, 100};
    EXPECT_EQ(tree.RoundLrootR(), ans);
    std::vector<int> ans2 = {100, 20, 10, 9, 8, 6, 1};
    EXPECT_EQ(tree.RoundRrootL(), ans2);
}

TEST(RBTreeTests, BigDataTests)
{
    const int N = 100000;
    std::vector<int> vec(N);
    for (int i = 0; i < N; i++)
    {
        vec[i] = i;
    }
    RBTree<int> tree(vec);
    EXPECT_TRUE(tree.contains(99999));
}
