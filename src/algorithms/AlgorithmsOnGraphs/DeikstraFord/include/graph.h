#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <tuple>

class Graph {
public:
    Graph(int vertices);
    
    void addEdge(int u, int v, int weight);
    int getVertices() const;
    const std::vector<std::pair<int, int>>& getNeighbors(int u) const;
    std::vector<std::tuple<int, int, int>> getEdges() const;

private:
    int vertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;
};

#endif