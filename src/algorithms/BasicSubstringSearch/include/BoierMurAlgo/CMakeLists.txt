cmake_minimum_required(VERSION 3.16)

project(BoierMurAlgo)

# Подставить имена файлов исходного кода
add_library(BoierMurAlgoLib SHARED ${PROJECT_SOURCE_DIR}/include/BoierMurAlgo.cpp ${PROJECT_SOURCE_DIR}/include/BoierMurAlgo.hpp)

# Подставить имена файлов исходного кода тестов
add_executable(BoierMurAlgoTests ${PROJECT_SOURCE_DIR}/tests/BoierMurAlgo.Tests.cpp)

target_link_libraries(BoierMurAlgoTests BoierMurAlgoLib gtest_main gtest pthread)