cmake_minimum_required(VERSION 3.16)

project(RabinCarpAlgo)

# Подставить имена файлов исходного кода
add_library(RabinCarpAlgoLib SHARED ${PROJECT_SOURCE_DIR}/include/RabinCarpAlgo.cpp ${PROJECT_SOURCE_DIR}/include/RabinCarpAlgo.hpp)

# Подставить имена файлов исходного кода тестов
add_executable(RabinCarpAlgoTests ${PROJECT_SOURCE_DIR}/tests/RabinCarpAlgo.Tests.cpp)

target_link_libraries(RabinCarpAlgoTests RabinCarpAlgoLib gtest_main gtest pthread)