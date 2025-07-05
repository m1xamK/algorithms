#include <gtest/gtest.h>
#include <../include/HeapSort.hpp>

int* ASCArray(int size)
{
    int* resArr = new int[size] {};
    for (int i = 0; i < size; ++i)
        resArr[i] = i + 1;

    return resArr;
}

int* DSCArray(int size)
{
    int* resArr = new int[size] {};
    for (int i = 0; i < size; ++i)
        resArr[size - 1 - i] = i;

    return resArr;
}

int* RandArray(int size)
{
    int* arr = new int[size] {};
    for (int i = 0; i < size; ++i)
        arr[i] = std::rand();

    return arr;
}


int* RandRepArray(int size)
{
    int* arr = new int[size] {};
    for (int i = 0; i < size; ++i)
        arr[i] = std::rand() % 1000;

    return arr;
}

struct paramList
{
    int len;
    int* in = new int[len];
};

class TestHeapSort : public ::testing::TestWithParam<struct paramList>
{};


TEST_P(TestHeapSort, HeapSort)
{
    int len = GetParam().len;
    int* in = GetParam().in;

    heapSort(in, len);
    EXPECT_TRUE(std::is_sorted(in, in + len));
}


int len = 12000;
int* ASCArr = ASCArray(len);
int* DSCArr = DSCArray(len);
int* randArr = RandArray(len);
int* repArr = RandRepArray(len);

INSTANTIATE_TEST_CASE_P(
    TestHeapSort,
    TestHeapSort,
    ::testing::Values(paramList{ len, ASCArr }, paramList{ len, DSCArr },
        paramList{ len, randArr }, paramList{ len, repArr }));
