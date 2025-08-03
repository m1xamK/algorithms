#include "../include/graph.h"
#include <climits>
#include <stdexcept>
#include <vector>

std::vector<int> bellmanFord(const Graph& graph, int source) {
    const int V = graph.getVertices();
    std::vector<int> dist(V, INT_MAX);
    dist[source] = 0;
    
    auto edges = graph.getEdges();
    const int E = edges.size();
    
    // Релаксация ребер (V-1 раз)
    for (int i = 1; i < V; ++i) {
        for (const auto& edge : edges) {
            int u = std::get<0>(edge);
            int v = std::get<1>(edge);
            int w = std::get<2>(edge);
            
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    // Проверка на отрицательные циклы
    for (const auto& edge : edges) {
        int u = std::get<0>(edge);
        int v = std::get<1>(edge);
        int w = std::get<2>(edge);
        
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            throw std::runtime_error("Обнаружен цикл отрицательного веса");
        }
    }
    
    return dist;
}