#include <gtest/gtest.h>
#include <vector>
#include <../include/ShellSort.h>
#include <algorithm>

using namespace std;

TEST(
        intTest,
        smallArray
) {
    vector<int> array = {4, 3, 12, 4, 1234, 54, -1, 44, 3, 2, 44, 8, 12, 5}, cop(array);
    vector<int> gap = {10, 20, 1};
    sort(array.begin(), array.end());

    shellSort<int>(cop, gap);

    ASSERT_EQ(array, cop);
}

TEST(
        intTest,
        bigArrayFibonach
) {

    vector<int> array;
    for(int i = 10000; i > 0; --i)
        array.emplace_back(i);
    vector<int> cop(array);
    vector<int> gap = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    reverse(gap.begin(), gap.end());
    sort(array.begin(), array.end());

    shellSort<int>(cop, gap);

    ASSERT_EQ(array, cop);
}

TEST(
        charTest,
        smallArray
) {
    vector<char> array = {4, 3, 12, 4, 127, 54, -1, 44, 3, 2, 44, 8, 12, 5}, cop(array);
    vector<int> gap = {10, 20, 1};
    sort(array.begin(), array.end());

    shellSort<char>(cop, gap);

    ASSERT_EQ(array, cop);
}


TEST(
        charTest,
        bigArrayFibonach
) {
    vector<char> array;
    for(int i = 10000; i > 0; --i)
        array.emplace_back(i);
    vector<char> cop(array);
    vector<int> gap = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    reverse(gap.begin(), gap.end());
    sort(array.begin(), array.end());

    shellSort<char>(cop, gap);

    ASSERT_EQ(array, cop);
}
