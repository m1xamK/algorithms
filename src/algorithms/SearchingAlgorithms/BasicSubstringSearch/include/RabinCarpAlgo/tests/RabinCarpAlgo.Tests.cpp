#include <gtest/gtest.h>
#include "../include/RabinCarpAlgo.hpp"
#include <climits>
#include <fstream>

TEST(RabinKarbAlgorithmTests, SimpleTest) {
    int q = INT_MAX;

    std::string txt = "GEEKS FOR GEEKS";
    std::string pat = "GEEK";
    std::vector<size_t> arr;

    searchRabinCarp(pat, txt, q, arr);
    
    ASSERT_EQ(2, arr.size());

    ASSERT_EQ(0, searchRabinCarp(pat, txt, q));

    txt = "EEKS FOR GEEKS";

    ASSERT_EQ(9, searchRabinCarp(pat, txt, q));

    txt = "EEKS FOR EEKS";

    ASSERT_EQ(std::string::npos, searchRabinCarp(pat, txt, q));
}


TEST(TimeTests, SimpleTest) {
    auto begin = clock();
    auto end = clock();
    int q = INT_MAX;

    std::fstream file("../../search/tests/data/1.txt");
    if (!file.is_open()) {
        std::cout << "file is not open";
    }
    std::string txt, buf;
    getline(file, txt);
    std::string pat = "ABCD";

    size_t a;

    begin = clock();
    a = searchRabinCarp(pat, txt, q);
    end = clock();

    std::cout << "Rabin-Carp: " << (double)(end - begin) / CLOCKS_PER_SEC << "s    at  " << a << std::endl;

    file.close();
}

TEST(TimeTests, WarAndPeaceOneWordTest) {
    auto begin = clock();
    auto end = clock();
    int q = INT_MAX;

    std::fstream file("../../search/tests/data/WAP.txt");
    if (!file.is_open()) {
        std::cout << "file is not open";
    }
    std::string txt, buf;
    for (size_t i = 0; i < 5000; ++i) {
        getline(file, buf);
        txt += buf;
    }
    std::string pat = "blockhead Alpatych";

    size_t a;

    begin = clock();
    a = searchRabinCarp(pat, txt, q);
    end = clock();

    std::cout << "Rabin-Carp: " << (double)(end - begin) / CLOCKS_PER_SEC << "s    at  " << a << std::endl;

    file.close();
}

TEST(TimeTests, WarAndPeaceSeveralWordsTest) {
    auto begin = clock();
    auto end = clock();
    int q = INT_MAX;
    std::vector<size_t> arr1, arr2;

    std::fstream file("../../search/tests/data/WAP.txt");
    if (!file.is_open()) {
        std::cout << "file is not open";
    }
    std::string txt, buf;
    for (size_t i = 0; i < 28900; ++i) {
        getline(file, buf);
        txt += buf;
    }
    std::string pat = "The specialized historian, describing the campaign of the year thirteen, or the restoration of the Bourbons, says directly that these events were produced by the will of Alexander. But the general historian Gervinus, disproving this view of the specialized historian, aims to show that the campaign of the year thirteen and the restoration of the Bourbons had as their causes, besides the will of Alexander, the activity of Stein, Metternich, Mme de Sta&#235;l, Talleyrand, Fichte, Chateaubriand, and others. The historian has obviously broken down the power of Alexander into its components: Talleyrand, Chateaubriand, and so on; the sum of these components, that is, the mutual influence on each other of Chateaubriand, Talleyrand, Mme de Sta&#235;l, and others, obviously does not equal the whole resultant, that is, the phenomenon that millions of Frenchmen submitted to the Bourbons. From the fact that Chateaubriand, Mme de Sta&#235;l, and others said such-and-such words to each other, there follows only their relations among themselves, not the submission of millions. And therefore, in order to explain in what way the submission of millions followed from their relations, that is, how from components equal to one A there followed a resultant equal to a thousand times A, the historian must necessarily allow again for the same force of the power which he denies, recognizing it as the result of forces, that is, he must allow for the unexplained force acting upon the composite. This is what general historians do. And consequently they contradict not only the specialized historians, but also themselves.";

    size_t a;

    begin = clock();
    a = searchRabinCarp(pat, txt, q, arr1);
    end = clock();

    std::cout << "Rabin-Carp: " << (double)(end - begin) / CLOCKS_PER_SEC << "s    at  " << a << std::endl;

    file.close();
}

TEST(TimeTests, ManySameLinesTest) {
    auto begin = clock();
    auto end = clock();
    int q = INT_MAX;
    std::vector<size_t> arr1, arr2, arr3, arr4;

    std::fstream file("../../search/tests/data/2.txt");
    if (!file.is_open()) {
        std::cout << "file is not open";
    }
    std::string txt, buf;
    for (size_t i = 0; i < 10800; ++i) {
        getline(file, buf);
        txt += buf;
    }
    std::string pat = "abcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //std::string pat = "abcdefghijklmanopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t a, b, c, d;

    begin = clock();
    a = searchRabinCarp(pat, txt, q, arr1);
    end = clock();

    std::cout << "Rabin-Carp: " << (double)(end - begin) / CLOCKS_PER_SEC << "s    at  " << a << std::endl;

    std::cout << "for       " << arr1.size() << "   times";

    file.close();
}
