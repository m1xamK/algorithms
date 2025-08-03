project(Algoritm_Prima)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Threads REQUIRED)

add_executable(Algoritm_Prima
        include/Prim.h
        tests/Prim.tests.cpp
)

target_link_libraries(Algoritm_Prima GTest::GTest GTest::Main)