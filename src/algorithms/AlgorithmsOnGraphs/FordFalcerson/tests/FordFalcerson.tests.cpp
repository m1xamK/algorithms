#include <gtest/gtest.h>
#include <vector>
#include "FordFalcerson/FordFalcerson.hpp"

TEST(MaxFlow, FordFalkersonTests1) {
    std::vector<std::tuple<int, int, int>> L = {{0, 1, 7}, {0, 2, 4}, {1, 2, 4}, {1, 3, 2}, {2, 3, 8}, {2, 4, 4}, {3, 4, 4}, {3, 5, 5}, {4, 5, 12}};
    int v_start = 0;
    int v_end = 5;
    int max_flow = FordFalkerson(L, 6, v_start, v_end);
    EXPECT_EQ(max_flow, 10);
}

TEST(MaxFlow, FordFalkersonTests2) {
    std::vector<std::tuple<int, int, int>> L = {{0, 1, 10}, {0, 2, 7}, {1, 3, 16}, {2, 3, 19}, {2, 4, 7}, {3, 5, 19}, {4, 5, 16}};
    int v_start = 0;
    int v_end = 5;
    int max_flow = FordFalkerson(L, 6, v_start, v_end);
    EXPECT_EQ(max_flow, 17);
}

