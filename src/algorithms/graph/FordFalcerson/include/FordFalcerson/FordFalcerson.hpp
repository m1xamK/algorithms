#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <list>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <tuple>

std::vector<std::pair<int, int>> DFS(const std::vector<std::list<int>>& L, int n, int v);

int FordFalkerson(std::vector<std::tuple<int, int, int>> L, int n, int v_start, int v_stop);

#endif