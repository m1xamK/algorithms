#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>

class Graph;

std::vector<int> dijkstra(const Graph& graph, int source);
std::vector<int> bellmanFord(const Graph& graph, int source);

#endif