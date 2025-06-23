cmake_minimum_required(VERSION 3.16)

project(FiniteAutomatAlgo)

# Подставить имена файлов исходного кода
add_library(FiniteAutomatAlgoLib SHARED ${PROJECT_SOURCE_DIR}/include/FiniteAutomatAlgo.cpp ${PROJECT_SOURCE_DIR}/include/FiniteAutomatAlgo.hpp)

# Подставить имена файлов исходного кода тестов
add_executable(FiniteAutomatAlgoTests ${PROJECT_SOURCE_DIR}/tests/FiniteAutomatAlgo.Tests.cpp)

target_link_libraries(FiniteAutomatAlgoTests FiniteAutomatAlgoLib gtest_main gtest pthread)