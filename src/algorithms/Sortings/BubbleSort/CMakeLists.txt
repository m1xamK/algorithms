cmake_minimum_required(VERSION 3.14)
project(BubbleSort)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем директорию с заголовками
include_directories(include)

# Добавляем исполняемый файл и его зависимости
add_executable(BubbleSort.tests tests/BubbleSort.tests.cpp)

# Линкуем с GTest и pthread
target_link_libraries(BubbleSort.tests gtest gtest_main pthread)
