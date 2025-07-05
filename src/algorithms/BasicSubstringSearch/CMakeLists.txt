cmake_minimum_required(VERSION 3.16)

project(search)

# Подставить имена файлов исходного кода
add_library(searchLib SHARED ${PROJECT_SOURCE_DIR}/src/search.cpp ${PROJECT_SOURCE_DIR}/src/search.hpp)

# Подставить имена файлов исходного кода тестов
add_executable(searchTests ${PROJECT_SOURCE_DIR}/tests/search.Tests.cpp)

target_link_libraries(searchTests searchLib gtest_main gtest pthread)