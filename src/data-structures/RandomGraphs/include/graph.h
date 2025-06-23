#pragma once
#include <vector>
#include <string>
#include <cstdint>

using Edge = std::pair<int,int>;          // неориентированное ребро
std::vector<Edge> gen_erdos_renyi(int n, double p);
bool connected(int n, const std::vector<Edge>& E);
double avg_path_len(int n, const std::vector<Edge>& E, int samples);
std::vector<int> greedy_coloring(int n, const std::vector<Edge>& E);
double edge_resilience(int n, const std::vector<Edge>& E, int k, int repeats);
std::string to_dot(int n, const std::vector<Edge>& E, const std::vector<int>* colors, const std::string& label);