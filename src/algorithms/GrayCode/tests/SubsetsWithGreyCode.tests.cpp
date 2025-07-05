#include <gtest/gtest.h>
#include <../include/SubsetsWithGreyCode/SubsetsWithGreyCode.hpp>


/**
 * function CheckElementInSequence - help function for tests, check if an element is in given array
 * @param const T value Template checked value
 * @param const std::vector<T> sequence Template sequence

 * @return bool In / not in sequence
 */
template<typename T>
bool CheckElementInSequence(const T value, const std::vector<T> sequence) {
    for (int i = 0; i < sequence.size(); ++i) {
        if (value == sequence[i]) {
            return true;
        }
    }
    return false;
}


/**
 * Parameterized tests to check Subsets generation for int values (6 tests)
 */
struct paramListForIntSubsetsGeneration {
    int** (*function)(int size);
    const std::vector<int> sequence;
    std::vector<std::vector<int>> expected;
};

class IntGenerateSubsetsTest : public ::testing::TestWithParam<struct paramListForIntSubsetsGeneration> {};

TEST_P(IntGenerateSubsetsTest, SubsetsGeneration) {
    const std::vector<int> sequence = GetParam().sequence;
    int size = sequence.size();
    int** (*function)(int);
    function = GetParam().function;
    std::vector<std::vector<int>> expected = GetParam().expected;
    std::vector<std::vector<int>> result = GenerateSubsets(sequence, function);

    for (int i = 0; i < pow(2, size); ++i) {
        for (int j = 0; j < size; ++j) {
            if (result[i][j] == int() && expected[i][j] == int()) {
                ASSERT_EQ(result[i][j], expected[i][j]);
                continue;
            }
            if (CheckElementInSequence(result[i][j], sequence) && CheckElementInSequence(expected[i][j], sequence)) {
                ASSERT_EQ(result[i][j], expected[i][j]);
            }
        }
    }
}

std::vector<int> intSingleSubset = { 10 };
std::vector<int> intTwoSubset = { 10, 20 };
std::vector<int> intThreeSubset = { 10, 20, 30 };

std::vector<std::vector<int>> intSingleDigitExpectedGeneratedSubsets = { { int() }, { 10 } };
std::vector<std::vector<int>> intTwoDigitExpectedGeneratedSubsets = { { int() }, { 20 }, { 10, 20 }, { 10 } };
std::vector<std::vector<int>> intThreeDigitExpectedGeneratedSubsets = { { int() }, { 30 }, { 20, 30 },
                                                                        { 20 }, { 10, 20 }, { 10, 20, 30 },
                                                                        { 10, 30 }, { 10 } };

INSTANTIATE_TEST_CASE_P(
        IntGenerateSubsetsTest,
        IntGenerateSubsetsTest,
        ::testing::Values(
                paramListForIntSubsetsGeneration{ GrayCode, intSingleSubset, intSingleDigitExpectedGeneratedSubsets },
                paramListForIntSubsetsGeneration{ GrayCode, intTwoSubset, intTwoDigitExpectedGeneratedSubsets },
                paramListForIntSubsetsGeneration{ GrayCode, intThreeSubset, intThreeDigitExpectedGeneratedSubsets },

                paramListForIntSubsetsGeneration{ RecursiveGrayCode, intSingleSubset, intSingleDigitExpectedGeneratedSubsets },
                paramListForIntSubsetsGeneration{ RecursiveGrayCode, intTwoSubset, intTwoDigitExpectedGeneratedSubsets },
                paramListForIntSubsetsGeneration{ RecursiveGrayCode, intThreeSubset, intThreeDigitExpectedGeneratedSubsets }
        ));


/**
 * Parameterized tests to check Subsets generation for double values (6 tests)
 */
struct paramListForDoubleSubsetsGeneration {
    int** (*function)(int size);
    std::vector<double> sequence;
    std::vector<std::vector<double>> expected;
};

class DoubleGenerateSubsetsTest : public ::testing::TestWithParam<struct paramListForDoubleSubsetsGeneration> {};

TEST_P(DoubleGenerateSubsetsTest, SubsetsGeneration) {
    std::vector<double> sequence = GetParam().sequence;
    int size = sequence.size();
    int** (*function)(int);
    function = GetParam().function;
    std::vector<std::vector<double>> expected = GetParam().expected;
    std::vector<std::vector<double>> result = GenerateSubsets(sequence, function);

    for (int i = 0; i < pow(2, size); ++i) {
        for (int j = 0; j < size; ++j) {
            if (result[i][j] == double() && expected[i][j] == double()) {
                ASSERT_EQ(result[i][j], expected[i][j]);
                continue;
            }
            if (CheckElementInSequence(result[i][j], sequence) && CheckElementInSequence(expected[i][j], sequence)) {
                ASSERT_EQ(result[i][j], expected[i][j]);
            }
        }
    }
}

std::vector<double> doubleSingleSubset = { 10.1 };
std::vector<double> doubleTwoSubset = { 10.1, 20.2 };
std::vector<double> doubleThreeSubset = { 10.1, 20.2, 30.3 };

std::vector<std::vector<double>> doubleSingleDigitExpectedGeneratedSubsets = { { double() }, { 10.1 } };
std::vector<std::vector<double>> doubleTwoDigitExpectedGeneratedSubsets = { { double() }, { 20.2 }, { 10.1, 20.2 }, { 10.1 } };
std::vector<std::vector<double>> doubleThreeDigitExpectedGeneratedSubsets = { { double() }, { 30.3 }, { 20.2, 30.3 },
                                                                              { 20.2 }, { 10.1, 20.2 },
                                                                              { 10.1, 20.2, 30.3 },
                                                                              { 10.1, 30.3 }, { 10.1 } };

INSTANTIATE_TEST_CASE_P(
        DoubleGenerateSubsetsTest,
        DoubleGenerateSubsetsTest,
        ::testing::Values(
                paramListForDoubleSubsetsGeneration{ GrayCode, doubleSingleSubset, doubleSingleDigitExpectedGeneratedSubsets },
                paramListForDoubleSubsetsGeneration{ GrayCode, doubleTwoSubset, doubleTwoDigitExpectedGeneratedSubsets },
                paramListForDoubleSubsetsGeneration{ GrayCode, doubleThreeSubset, doubleThreeDigitExpectedGeneratedSubsets },

                paramListForDoubleSubsetsGeneration{ RecursiveGrayCode, doubleSingleSubset, doubleSingleDigitExpectedGeneratedSubsets },
                paramListForDoubleSubsetsGeneration{ RecursiveGrayCode, doubleTwoSubset, doubleTwoDigitExpectedGeneratedSubsets },
                paramListForDoubleSubsetsGeneration{ RecursiveGrayCode, doubleThreeSubset, doubleThreeDigitExpectedGeneratedSubsets }
        ));


/**
 * Parameterized tests to check Subsets generation for char values (6 tests)
 */
struct paramListForCharSubsetsGeneration {
    int** (*function)(int size);
    std::vector<char> sequence;
    std::vector<std::vector<char>> expected;
};

class CharGenerateSubsetsTest : public ::testing::TestWithParam<struct paramListForCharSubsetsGeneration> {};

TEST_P(CharGenerateSubsetsTest, SubsetsGeneration) {
    std::vector<char> sequence = GetParam().sequence;
    int size = sequence.size();
    int** (*function)(int);
    function = GetParam().function;
    std::vector<std::vector<char>> expected = GetParam().expected;
    std::vector<std::vector<char>> result = GenerateSubsets(sequence, function);

    for (int i = 0; i < pow(2, size); ++i) {
        for (int j = 0; j < size; ++j) {
            if (result[i][j] == char() && expected[i][j] == char()) {
                ASSERT_EQ(result[i][j], expected[i][j]);
                continue;
            }
            if (CheckElementInSequence(result[i][j], sequence) && CheckElementInSequence(expected[i][j], sequence)) {
                ASSERT_EQ(result[i][j], expected[i][j]);
            }
        }
    }
}

std::vector<char> charSingleSubset = { 'A' };
std::vector<char> charTwoSubset = { 'A', 'B' };
std::vector<char> charThreeSubset = { 'A', 'B', 'C' };

std::vector<std::vector<char>> charSingleDigitExpectedGeneratedSubsets = { { char() }, { 'A' } };
std::vector<std::vector<char>> charTwoDigitExpectedGeneratedSubsets = { { char() }, { 'B' }, { 'A', 'B' }, { 'A' } };
std::vector<std::vector<char>> charThreeDigitExpectedGeneratedSubsets = { { char() }, { 'C' }, { 'B', 'C' },
                                                                          { 'B' }, { 'A', 'B' }, { 'A', 'B', 'C' },
                                                                          { 'A', 'C' }, { 'A' } };

INSTANTIATE_TEST_CASE_P(
        CharGenerateSubsetsTest,
        CharGenerateSubsetsTest,
        ::testing::Values(
                paramListForCharSubsetsGeneration{ GrayCode, charSingleSubset, charSingleDigitExpectedGeneratedSubsets },
                paramListForCharSubsetsGeneration{ GrayCode, charTwoSubset, charTwoDigitExpectedGeneratedSubsets },
                paramListForCharSubsetsGeneration{ GrayCode, charThreeSubset, charThreeDigitExpectedGeneratedSubsets },

                paramListForCharSubsetsGeneration{ RecursiveGrayCode, charSingleSubset, charSingleDigitExpectedGeneratedSubsets },
                paramListForCharSubsetsGeneration{ RecursiveGrayCode, charTwoSubset, charTwoDigitExpectedGeneratedSubsets },
                paramListForCharSubsetsGeneration{ RecursiveGrayCode, charThreeSubset, charThreeDigitExpectedGeneratedSubsets }
        ));
