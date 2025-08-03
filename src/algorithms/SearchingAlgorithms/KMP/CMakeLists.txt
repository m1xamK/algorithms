cmake_minimum_required(VERSION 3.14)
project(KMP)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
add_library(KMP src/KMP.cpp)
add_executable(KMP.tests tests/KMP.tests.cpp)

target_link_libraries(KMP.tests KMP gtest gtest_main pthread)
