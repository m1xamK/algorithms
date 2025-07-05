cmake_minimum_required(VERSION 3.14)

project(AVLTree)

#include_directories(include)

#add_subdirectory(src)
#add_subdirectory(tests)

add_library(AVLTreeLib SHARED include/AVLTree/AVLTree.hpp include/AVLTree/TreeNode.hpp src/AVLTree.cpp)

# source code test file names
add_executable(AVLTreeTests tests/AVLTree.tests.cpp)

target_link_libraries(AVLTreeTests AVLTreeLib gtest_main gtest pthread)