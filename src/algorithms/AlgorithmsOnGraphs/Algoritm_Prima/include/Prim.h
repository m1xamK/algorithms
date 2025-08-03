// #include <graphviz/gvc.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <random>
#include <algorithm>

// ===================== Edge Struct =====================
struct Edge {
    int weight;
    int from;
    int to;
};

// ===================== Graph Class =====================
class Graph {
private:
    int numVertices;
    int minWeight, maxWeight;
    bool makeComplete;
    std::vector<Edge> edges;

    int randomInt(int min, int max) {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(min, max);
        return dist(gen);
    }

    bool edgeExists(int u, int v) {
        for (const auto& e : edges)
            if ((e.from == u && e.to == v) || (e.from == v && e.to == u))
                return true;
        return false;
    }

public:
    Graph(int n, int minW = 1, int maxW = 10, bool complete = false)
        : numVertices(n), minWeight(minW), maxWeight(maxW), makeComplete(complete) {}

    void generate() {
        edges.clear();

        std::vector<int> nodes(numVertices);
        for (int i = 0; i < numVertices; ++i) nodes[i] = i;
        std::shuffle(nodes.begin(), nodes.end(), std::mt19937(std::random_device()()));

        std::unordered_set<int> visited = {nodes[0]};

        while (visited.size() < numVertices) {
            int u = *std::next(visited.begin(), randomInt(0, visited.size() - 1));
            int v;
            do {
                v = nodes[randomInt(0, numVertices - 1)];
            } while (visited.count(v));

            edges.push_back({randomInt(minWeight, maxWeight), u, v});
            visited.insert(v);
        }

        if (makeComplete) {
            for (int i = 0; i < numVertices; ++i) {
                for (int j = i + 1; j < numVertices; ++j) {
                    if (!edgeExists(i, j)) {
                        edges.push_back({randomInt(minWeight, maxWeight), i, j});
                    }
                }
            }
        }
    }

    void print() const {
        std::cout << "Graph with " << numVertices << " vertices and " << edges.size() << " edges:\n";
        for (const auto& e : edges)
            std::cout << e.from << " - " << e.to << " : " << e.weight << "\n";
    }

    const std::vector<Edge>& getEdges() const { return edges; }
    int getVertexCount() const { return numVertices; }

    void drawGraph(const std::string& filename) const {
        std::ofstream file(filename);
        file << "graph G {\n";
        for (const auto& edge : edges) {
            file << "    " << edge.from << " -- " << edge.to
                 << " [label=\"" << edge.weight << "\"];\n";
        }
        file << "}\n";
        file.close();

        std::string cmd = "dot -Tpng " + filename + " -o graph.png";
        int result = system(cmd.c_str());
        if (result == 0) {
            std::cout << "Graph image saved as graph.png\n";
        } else {
            std::cerr << "Failed to generate graph image.\n";
        }
    }

};

// ===================== Prim Class =====================
class Prim {
public:
    static std::vector<Edge> mst(const Graph& graph) {
        int n = graph.getVertexCount();
        const auto& allEdges = graph.getEdges();

        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (const auto& e : allEdges) {
            adj[e.from].emplace_back(e.to, e.weight);
            adj[e.to].emplace_back(e.from, e.weight);
        }

        std::vector<bool> inMST(n, false);
        std::vector<Edge> mstEdges;
        using QueueEdge = std::pair<int, std::pair<int, int>>;
        std::priority_queue<QueueEdge, std::vector<QueueEdge>, std::greater<>> pq;

        inMST[0] = true;
        for (const auto& [to, weight] : adj[0]) {
            pq.push({weight, {0, to}});
        }

        while (!pq.empty() && mstEdges.size() < n - 1) {
            auto [weight, nodes] = pq.top(); pq.pop();
            int u = nodes.first, v = nodes.second;
            if (inMST[v]) continue;

            inMST[v] = true;
            mstEdges.push_back({weight, u, v});

            for (const auto& [next, w] : adj[v]) {
                if (!inMST[next])
                    pq.push({w, {v, next}});
            }
        }

        return mstEdges;
    }

    static void print(const std::vector<Edge>& mstEdges) {
        int totalWeight = 0;
        std::cout << "Minimum Spanning Tree:\n";
        for (const auto& e : mstEdges) {
            std::cout << e.from << " - " << e.to << " : " << e.weight << "\n";
            totalWeight += e.weight;
        }
        std::cout << "Total weight: " << totalWeight << "\n";
    }

    static void drawMST(const std::string& filename, const std::vector<Edge>& mstEdges) {
        std::ofstream file(filename);
        file << "graph MST {\n";
        for (const auto& edge : mstEdges) {
            file << "    " << edge.from << " -- " << edge.to
                 << " [label=\"" << edge.weight
                 << "\", color=blue, penwidth=2.0];\n";
        }
        file << "}\n";
        file.close();

        std::string cmd = "dot -Tpng " + filename + " -o mst.png";
        int result = system(cmd.c_str());
        if (result == 0) {
            std::cout << "MST image saved as mst.png\n";
        } else {
            std::cerr << "Failed to generate MST image.\n";
        }
    }

};



