#include "../include/graph.h"

Graph::Graph(int vertices) 
    : vertices(vertices), adjList(vertices) {}

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].push_back({v, weight});
}

int Graph::getVertices() const {
    return vertices;
}

const std::vector<std::pair<int, int>>& Graph::getNeighbors(int u) const {
    return adjList[u];
}

std::vector<std::tuple<int, int, int>> Graph::getEdges() const {
    std::vector<std::tuple<int, int, int>> edges;
    for (int u = 0; u < vertices; ++u) {
        for (const auto& neighbor : adjList[u]) {
            edges.push_back(std::make_tuple(u, neighbor.first, neighbor.second));
        }
    }
    return edges;
}