#include "../include/Prim.h"
#include <gtest/gtest.h>
#include <gtest/gtest.h>




TEST(PrimAlgorithmTest, MSTWeightNotGreaterThanOriginal) {
    Graph g(12, 1, 10, true);
    g.generate();
    auto mst = Prim::mst(g);

    int totalOriginal = 0;
    for (const auto& e : g.getEdges())
        totalOriginal += e.weight;

    int totalMST = 0;
    for (const auto& e : mst)
        totalMST += e.weight;

    EXPECT_LE(totalMST, totalOriginal);
}


TEST(PrimAlgorithmTest, MSTHasCorrectEdgeCount) {
    Graph g(8, 1, 10, true);
    g.generate();

    auto mst = Prim::mst(g);
    EXPECT_EQ(mst.size(), g.getVertexCount() - 1);  // MST всегда имеет V-1 рёбер
}


TEST(GraphGenerationTest, GeneratesConnectedGraph) {
    Graph g(10);
    g.generate();
    const auto& edges = g.getEdges();

    std::unordered_set<int> nodes;
    for (const auto& e : edges) {
        nodes.insert(e.from);
        nodes.insert(e.to);
    }

    EXPECT_EQ(nodes.size(), 10); // Должны быть все вершины
    EXPECT_GE(edges.size(), 9);  // Для связного графа минимум n-1 ребро
}


TEST(IntegrationTest, GenerateGraphAndDrawMST) {
    // 1. Генерация графа
    Graph g(5 , 1 , 5 , true);
    g.generate();

    // 2. Отрисовка исходного графа
    g.drawGraph("integration_graph.dot");

    // 3. Построение MST
    auto mst = Prim::mst(g);

    // 4. Отрисовка MST
    Prim::drawMST("integration_mst.dot", mst);

    // 5. Проверка: MST должен содержать V - 1 ребро
    EXPECT_EQ(mst.size(), g.getVertexCount() - 1);

    // 6. Проверка: Все вершины должны быть покрыты MST
    std::unordered_set<int> covered;
    for (const auto& edge : mst) {
        covered.insert(edge.from);
        covered.insert(edge.to);
    }
    EXPECT_EQ(covered.size(), g.getVertexCount());

    // 7. Проверка, что картинки были сгенерированы
    std::ifstream graphImg("graph.png");
    std::ifstream mstImg("mst.png");
    EXPECT_TRUE(graphImg.good());
    EXPECT_TRUE(mstImg.good());
}


