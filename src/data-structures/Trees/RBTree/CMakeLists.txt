cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(RBTree)

include_directories(include)

add_subdirectory(src)

add_subdirectory(tests)