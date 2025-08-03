cmake_minimum_required(VERSION 3.15)

project(DDZ_MSD)

add_library(DDZ_MSDLib SHARED src/msd_sort.cpp)

add_executable(DDZ_MSDTests tests/msd_sort.tests.cpp)

target_link_libraries(DDZ_MSDTests DDZ_MSDLib gtest_main gtest pthread)