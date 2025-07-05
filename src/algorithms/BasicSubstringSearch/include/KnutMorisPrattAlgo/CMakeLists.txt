cmake_minimum_required(VERSION 3.16)

project(KnutMorisPrattAlgo)

# Подставить имена файлов исходного кода
add_library(KnutMorisPrattAlgoLib SHARED ${PROJECT_SOURCE_DIR}/include/KnutMorisPrattAlgo.cpp ${PROJECT_SOURCE_DIR}/include/KnutMorisPrattAlgo.hpp)

# Подставить имена файлов исходного кода тестов
add_executable(KnutMorisPrattAlgoTests ${PROJECT_SOURCE_DIR}/tests/KnutMorisPrattAlgo.Tests.cpp)

target_link_libraries(KnutMorisPrattAlgoTests KnutMorisPrattAlgoLib gtest_main gtest pthread)