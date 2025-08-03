cmake_minimum_required(VERSION 3.15)

project(fing_string)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(fstring tests/fing_string_tests.cpp)

target_link_libraries(fstring ${GTEST_LIBRARIES} pthread)
