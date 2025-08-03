cmake_minimum_required(VERSION 3.14)
project(DDZ)

include_directories(/usr/include) # Добавь этот каталог

add_executable(DDZTests tests/test_algorithms.cpp src/bellman_ford.cpp src/dijkstra.cpp src/graph.cpp)
target_link_libraries(DDZTests PRIVATE gtest_main gtest pthread)
