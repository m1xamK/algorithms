#include <gtest/gtest.h>
#include "../include/graph.h"
#include "../include/algorithms.h"
#include <climits>
#include <string>

void printDistances(const std::vector<int>& dist, const std::string& algorithm) {
    std::cout << "Кратчайшие пути (" << algorithm << "):\n";
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == INT_MAX) {
            std::cout << "Вершина " << i << ": недостижима\n";
        } else {
            std::cout << "Вершина " << i << ": " << dist[i] << '\n';
        }
    }
    std::cout << '\n';
}

// Юнит-тесты для алгоритма Дейкстры
TEST(DijkstraTest, PositiveWeights) {
    Graph graph(4);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 3, 5);
    
    auto dist = dijkstra(graph, 0);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 3);
    EXPECT_EQ(dist[2], 1);
    EXPECT_EQ(dist[3], 8);
}

// Юнит-тесты для алгоритма Беллмана-Форда
TEST(BellmanFordTest, NegativeWeights) {
    Graph graph(4);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 5);
    graph.addEdge(2, 1, -2);
    graph.addEdge(1, 3, 1);
    
    auto dist = bellmanFord(graph, 0);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 3);
    EXPECT_EQ(dist[2], 5);
    EXPECT_EQ(dist[3], 4);
}

TEST(BellmanFordTest, NegativeCycle) {
    Graph graph(3);
    graph.addEdge(0, 1, -1);
    graph.addEdge(1, 2, -3);
    graph.addEdge(2, 0, 2);
    
    EXPECT_THROW(bellmanFord(graph, 0), std::runtime_error);
}

// Демонстрационные тесты
TEST(DemoTest, Dijkstra) {
    // Граф для алгоритма Дейкстры (положительные веса)
    Graph graph(6);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 3, 3);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 1, 2);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 3, 1);

    auto dist = dijkstra(graph, 0);
    printDistances(dist, "Дейкстра");
}

TEST(DemoTest, BellmanFord) {
    // Граф для алгоритма Беллмана-Форда (отрицательные веса без циклов)
    Graph graph(6);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, -2);
    graph.addEdge(1, 4, 4);
    graph.addEdge(2, 1, -1);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 5, 3);
    
    auto dist = bellmanFord(graph, 0);
    printDistances(dist, "Беллман-Форд");
}

TEST(DemoTest, BellmanFordNegativeCycle) {
    // Граф с отрицательным циклом
    Graph graph(10);
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 3, -10);
    graph.addEdge(3, 1, 4);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 5, 2);
    graph.addEdge(5, 6, 3);
    graph.addEdge(6, 7, 1);
    graph.addEdge(7, 8, 4);
    graph.addEdge(8, 9, 2);

    EXPECT_THROW(bellmanFord(graph, 0), std::runtime_error);
}