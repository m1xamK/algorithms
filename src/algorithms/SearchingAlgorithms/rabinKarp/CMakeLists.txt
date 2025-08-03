cmake_minimum_required(VERSION 3.14)
project(rabin_karp)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
add_executable(rabin_karp.tests tests/rabin_karp.tests.cpp)

target_link_libraries(rabin_karp.tests gtest gtest_main pthread)