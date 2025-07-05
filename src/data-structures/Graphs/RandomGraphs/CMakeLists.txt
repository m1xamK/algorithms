cmake_minimum_required(VERSION 3.20)
project(RandomGraphs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------ библиотека с алгоритмами ------------------
add_library(src
    src/graph.cpp
    include/graph.h)                # удобнее сразу «видеть» заголовок
target_include_directories(src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# ------------------ Google Test -------------------------------
find_package(GTest REQUIRED)
enable_testing()

add_executable(RandomGraphs.tests tests/tests.cpp)

# главное: даём линковщику libsrc.a + GTest + pthread
target_link_libraries(RandomGraphs.tests
    PRIVATE
        src                     #  ← наша библиотека
        GTest::GTest            #  ← gtest
        GTest::Main             #  ← gtest_main
        pthread)                #  ← для Unix‐thread’ов
