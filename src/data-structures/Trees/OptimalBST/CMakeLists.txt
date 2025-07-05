cmake_minimum_required(VERSION 3.14)

project(MP_DDZ)

# Подставить имена файлов исходного кода
add_library(OptimalTreeLib SHARED ${PROJECT_SOURCE_DIR}/OptimalTree/OptimalTree.h ${PROJECT_SOURCE_DIR}/OptimalTree/OptimalTree.cpp)

# Подставить имена файлов исходного кода тестов
add_executable(Tests ${PROJECT_SOURCE_DIR}/OptimalTree/Tests/OptimalTree.tests.cpp)

target_link_libraries(Tests OptimalTreeLib gtest_main gtest pthread)