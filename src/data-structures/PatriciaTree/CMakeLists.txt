cmake_minimum_required(VERSION 3.14)

project(PatriciaTree)

# Подставить имена файлов исходного кода
add_library(PatriciaTreeLib SHARED include/PatriciaTree/PatriciaTree.hpp src/PatriciaTree.cpp)

# Подставить имена файлов исходного кода тестов
add_executable(PatriciaTreeTests tests/PatriciaTree.Tests.cpp)

target_link_libraries(PatriciaTreeTests PatriciaTreeLib gtest_main gtest pthread)
