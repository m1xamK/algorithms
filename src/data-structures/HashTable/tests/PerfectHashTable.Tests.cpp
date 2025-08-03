#include "../include/PerfectHashTable.h"
#include <gtest/gtest.h>

TEST(PerfectHashTableTest, EmptyTable) {
    PerfectHashTable<int> table({});
    EXPECT_FALSE(table.contains(0));
    EXPECT_FALSE(table.contains(1));
}

TEST(PerfectHashTableTest, SingleElement) {
    PerfectHashTable<int> table({ 42 });
    EXPECT_TRUE(table.contains(42));
    EXPECT_FALSE(table.contains(43));
}

TEST(PerfectHashTableTest, StringKeys) {
    std::vector<std::string> keys = { "apple", "banana", "cherry", "date", "elderberry" };
    PerfectHashTable<std::string> table(keys);

    for (const auto& key : keys) {
        EXPECT_TRUE(table.contains(key));
    }

    EXPECT_FALSE(table.contains("fig"));
    EXPECT_FALSE(table.contains(""));
}

TEST(PerfectHashTableTest, LargeSet) {
    std::vector<int> keys;
    for (int i = 0; i < 1000; i += 10) {
        keys.push_back(i);
    }

    PerfectHashTable<int> table(keys);

    for (int key : keys) {
        EXPECT_TRUE(table.contains(key));
    }

    for (int i = 1; i < 1000; i += 10) {
        EXPECT_FALSE(table.contains(i));
    }
}