cmake_minimum_required(VERSION 3.14)

project(mp_ddz)


add_library(PageRankLib SHARED PageRank/PageRank.h PageRank/PageRank.cpp)

add_executable(PageRankTests PageRank.Tests/test.cpp)

target_link_libraries(PageRankTests PageRankLib gtest_main gtest pthread)







