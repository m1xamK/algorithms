#include "../include/graph.h"
#include <gtest/gtest.h>
#include <numeric>
#include <cmath>
#include <cstdlib>      // std::system
#include <fstream>
#include <random>
#include <sstream>
#include <ranges> 
#include <algorithm>

static double foundedProbability = std::numeric_limits<double>::quiet_NaN();

static double fractionOfCorrectGraphs(const std::vector<bool>& v)
{
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

static double expectChromaticNumber(int n, double p)
{
    double lnB = std::log(1.0 / (1.0 - p));
    return n / (2.0 * (std::log(n) / lnB));
}

static double expectedProbabilityOfConnectivity(int n, double epsilon)
{
    return (std::log(n) + std::log(1.0 / epsilon)) / n;
}


// ищем веротяность ребра, при котороой граф на 10'000 врешинах будет связным 90 случаев из 100
TEST(P_Search, NinetyPercentTenTimes)
{
    constexpr int n    = 10'000;
    constexpr int M    = 100;           // графов на каждую проверку
    constexpr int STAB = 10;            // требуемая «устойчивость»
    double p = 0.0005;
    int ok_streak = 0;

    while (ok_streak < STAB)
    {
        std::vector<bool> ok(M);
        for (int i = 0; i < M; ++i)
            ok[i] = connected(n, gen_erdos_renyi(n, p));

        if (fractionOfCorrectGraphs(ok) >= 0.90){
            ++ok_streak;
        }
        else {
            ok_streak = 0;
        }

        p += 0.0005;   // шаг всё равно нужен, иначе зациклится
        ASSERT_LT(p, 0.1) << "p too large, something is wrong";
    }
    foundedProbability = p;          // p – уже увеличено на +0.0005, но это ок
    std::cout << "[INFO]  p* = " << foundedProbability << '\n';
    EXPECT_TRUE(foundedProbability > 0.0);
}

// проверка леммы о рукопожатиях(формулы, исложенной в README)
TEST(PathLenSixRealWorld, AroundSix)
{
    const int    n         = 50'000;
    const double k_target  = 6.0;                     // средняя степень вершины
    const double p         = k_target / (n - 1);      
    const int    GRAPHS    = 10;
    const int    BFS_SAMPLES = 60;

    double sumL = 0.0;
    for (int g = 0; g < GRAPHS; ++g)
        sumL += avg_path_len(n, gen_erdos_renyi(n, p), BFS_SAMPLES);

    double empiricalLength = sumL / GRAPHS;
    double theoreticalLength = std::log(n) / std::log(k_target);

    std::cout << "[INFO]  empiricalLength ≈ " << empiricalLength
              << "   (theoreticalLength ~ " << theoreticalLength << ")\n";

    EXPECT_GE(empiricalLength, 5.0);
    EXPECT_LE(empiricalLength, 7.0);
}


// Проверка формулы о создании графа, с заданной вероятностью связанности
TEST(ConnectivityFormula, EpsilonGuarantee)
{
    const int n   = 3'500;
    const double epsilon = 0.01;                // хотим ≥ 99 % связности
    const double p   = expectedProbabilityOfConnectivity(n, epsilon);

    int runs = 1000, ok = 0;
    for (int i=0;i<runs;++i)
        if (connected(n, gen_erdos_renyi(n, p))) ++ok;

    double freq = double(ok)/runs;
    std::cout << "[INFO]  connected freq = " << freq << '\n';
    EXPECT_GE(freq + 0.003, 1.0 - epsilon);
}


// достаточно грубая оценка для жадного хроматического числа, однако известно, что при увеличении n epsilon -> 0
TEST(GreedyVsTheory_BigN, TwoPointFiveBound)
{
    const int    n = 20'000;     
    const double p = 0.2;       
    const int    batches = 7;   
    double chromaticNumber = expectChromaticNumber(n, p);
    for (int i = 0; i < batches; ++i)
    {
        auto col = greedy_coloring(n, gen_erdos_renyi(n, p));
        int  greedychromaticNumber   = *std::max_element(col.begin(), col.end()) + 1;
        EXPECT_LE(greedychromaticNumber, 2.75 * chromaticNumber) << "batch " << i;
    }
}

// В графе с уже вычисленной вероятностью ребра ищем возмодное количество рёбер, которые можно удалить так, чтобы
// 10 раз подряд граф оставался связанным
TEST(VertexResilience, MaxSafeDeletionStable)
{
    ASSERT_FALSE(std::isnan(foundedProbability));
    double p = foundedProbability;
    int n = 10'000;
    auto G = gen_erdos_renyi(n, p);

    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> pick(0, n-1);

    auto survives = [&](int k)->bool
    {
        std::vector<char> gone(n);
        int removed = 0;
        while (removed < k)
        {
            int v = pick(rng);
            if (!gone[v]) { gone[v] = 1; ++removed; }
        }
        std::vector<int> map(n, -1); int new_id = 0;
        for (int v = 0; v < n; ++v) if (!gone[v]) map[v] = new_id++;

        std::vector<Edge> sub;
        sub.reserve(G.size());
        for (auto [u,v] : G)
            if (!gone[u] && !gone[v]) sub.emplace_back(map[u], map[v]);

        return connected(new_id, sub);
    };

    int k = 0, step = 50, streak = 0;
    while (streak < 10 && k + step < n/2)
    {
        if (survives(k + step)) { k += step; ++streak; }
        else streak = 0;
    }
    std::cout << "[INFO]  safe deletion k ≈ " << k << '\n';
    EXPECT_GT(k, n * 0.049);
}

// просто отрисовка раскрашенного графа, картинка лежит в /build/mini.png
TEST(GraphViz, DotRendered)
{
    using namespace std::string_literals;
    const int    n = 42;
    const double p = 0.2;            
    auto G = gen_erdos_renyi(n, p);
    auto C = greedy_coloring(n, G);

    std::ofstream("mini.dot") << to_dot(n, G, &C, "Mini ER");

    int rc = std::system(
        "timeout 15s sfdp -Tpng mini.dot -o mini.png > /dev/null 2>&1");

    EXPECT_EQ(rc, 0) << "GraphViz timed out or failed";
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}