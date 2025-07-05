cmake_minimum_required(VERSION 3.14)

project(BST)

add_executable(BSTTests BST.Tests/test.cpp)

target_link_libraries(BSTTests gtest_main gtest pthread)