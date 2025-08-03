cmake_minimum_required(VERSION 3.14)

project(Stepanino-bananino)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Stepanino-bananinoLib SHARED src/DDZ_MonkeySort.cpp )
add_executable(Stepanino-bananinoTests tests/DDZ_MonkeySort.Tests.cpp)

target_link_libraries(Stepanino-bananinoTests gmock_main gmock gtest pthread) 
