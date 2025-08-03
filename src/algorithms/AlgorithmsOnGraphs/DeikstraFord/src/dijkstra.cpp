#include "../include/graph.h"
#include <queue>
#include <climits>
#include <vector>
#include <functional>

std::vector<int> dijkstra(const Graph& graph, int source) {
    const int V = graph.getVertices();
    std::vector<int> dist(V, INT_MAX);
    dist[source] = 0;
    
    // Приоритетная очередь: (расстояние, вершина)
    using Vertex = std::pair<int, int>;
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        // Пропускаем устаревшие записи
        if (d != dist[u]) continue;
        
        // Обновляем расстояния до соседей
        for (const auto& neighbor : graph.getNeighbors(u)) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}