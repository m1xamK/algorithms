#include "../PageRank/PageRank.h"
#include <algorithm>
#include "gtest/gtest.h"



TEST(PageRank, DataFilesTests) {
    auto vec = getPageRank("data/heroes_network_674.csv");
    double eps = 0.0001;
    std::sort(vec.begin(), vec.end(), [](auto x, auto y) {return x.first > y.first; });
    std::vector<double> ans = { 0.000300484, 0.000300484, 0.000300484, 0.000237427, 0.000237427, 0.000237427, 0.000237427, 0.000237427, 0.000237427, 0.000237427 };
    for (std::size_t i = 0; i < 10; ++i) {
        EXPECT_TRUE(abs(vec[i].first - ans[i]) < eps);
        auto v = vec[i];
        std::cout << v.second << " " << v.first << std::endl;
    }
}

TEST(PageRank, BigDataFilesTests) {
    auto vec = getPageRank("data/heroes_network_6426.csv");
    double eps = 0.01;
    std::sort(vec.begin(), vec.end(), [](auto x, auto y) {return x.first > y.first; });
    std::vector<double> ans = { 0.0061063,0.00577776 ,0.00577776 ,0.00577776 ,0.00577776 };
    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_TRUE(abs(vec[i].first - ans[i]) < eps) << abs(vec[i].first - ans[i]);
        auto v = vec[i];
        std::cout << v.second << " " << v.first << std::endl;
    }
}


TEST(PageRank,FilesTests2) {
    auto vec = getPageRank("data/MyPeson.csv");
    double eps = 0.01;
    std::sort(vec.begin(), vec.end(), [](auto x, auto y) {return x.first > y.first; });
    std::vector<double> ans = {0.00086275, 0.00086275 , 0.000351923 , 0.000351923 , 0.000351923 };
    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_TRUE(abs(vec[i].first - ans[i]) < eps) << abs(vec[i].first - ans[i]);
        auto v = vec[i];
       std::cout << v.second << " " << abs(v.first) << std::endl;
    }
}