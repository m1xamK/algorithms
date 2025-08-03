#include "../include/HashTableChaining.h" 
#include <gtest/gtest.h>

TEST(HashTableChainingTest, Constructor) {
    HashTableChaining<int> table;
    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.size(), 0);

    HashTableChaining<std::string> table2(20, 0.5f);
    EXPECT_TRUE(table2.empty());
}

TEST(HashTableChainingTest, InsertAndContains) {
    HashTableChaining<int> table;

    table.insert(10);
    EXPECT_TRUE(table.contains(10));
    EXPECT_EQ(table.size(), 1);

    table.insert(20);
    EXPECT_TRUE(table.contains(20));
    EXPECT_EQ(table.size(), 2);

    // Проверка дубликатов
    table.insert(10);
    EXPECT_EQ(table.size(), 2);
}

TEST(HashTableChainingTest, Remove) {
    HashTableChaining<std::string> table;

    table.insert("apple");
    table.insert("banana");
    EXPECT_EQ(table.size(), 2);

    EXPECT_TRUE(table.remove("apple"));
    EXPECT_FALSE(table.contains("apple"));
    EXPECT_EQ(table.size(), 1);

    // Удаление несуществующего элемента
    EXPECT_FALSE(table.remove("orange"));
    EXPECT_EQ(table.size(), 1);
}

TEST(HashTableChainingTest, Rehashing) {
    HashTableChaining<int> table(5, 0.6f);

    for (int i = 0; i < 10; ++i) {
        table.insert(i);
    }

    EXPECT_EQ(table.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(table.contains(i));
    }
}

TEST(HashTableChainingTest, Collisions) {
    HashTableChaining<int> table(3);

    table.insert(1);
    table.insert(4); 
    table.insert(7);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(4));
    EXPECT_TRUE(table.contains(7));

    table.remove(4);
    EXPECT_FALSE(table.contains(4));
    EXPECT_TRUE(table.contains(7));
}

TEST(HashTableChainingTest, StressTest) {
    HashTableChaining<int> table;
    const int N = 1000;

    for (int i = 0; i < N; ++i) {
        table.insert(i);
    }

    EXPECT_EQ(table.size(), N);
    for (int i = 0; i < N; ++i) {
        EXPECT_TRUE(table.contains(i));
    }

    for (int i = 0; i < N; i += 2) {
        table.remove(i);
    }

    EXPECT_EQ(table.size(), N / 2);
    for (int i = 1; i < N; i += 2) {
        EXPECT_TRUE(table.contains(i));
    }
}