#include "../include/FordFalcerson/FordFalcerson.hpp"

// Алгоритм поиска в глубину
std::vector<std::pair<int, int>> DFS(const std::vector<std::list<int>>& L, int n, int v_start, int v_stop) {
    std::stack<std::pair<int, int>> st;
    std::set<int> visited;
    st.push({v_start, v_start});
    std::vector<std::pair<int, int>> ans;
    bool pathFound = false;
    while (!st.empty()) {
        std::pair<int, int> curr = st.top();
        st.pop();
        if (visited.find(curr.second) != visited.end())
            continue;
        visited.insert(curr.second);
        ans.push_back(curr);
        if (curr.second == v_stop) {
            pathFound = true;
            break;
        }
        for (auto e : L[curr.second])
            st.push({curr.second, e});

    }

    if (pathFound)
        return ans;
    else
        return {};
}

int FordFalkerson(std::vector<std::tuple<int, int, int>> L, int n, int v_start, int v_stop) {
    std::vector<std::list<int>> C(n);
    for(auto e : L) {
        auto [v1, v2, flow] = e;
        C[v1].push_back(v2);
    }
    auto path = DFS(C, n, v_start, v_stop); // Разбиваем граф на отрезки
    int min = 99999999;
    int max_flow = 0;
    while (path.size() > 0) { // Начало алгоритма Форда-Фалкерсона
        for (int i = 0; i < path.size(); ++i) {
            auto [v1, v2] = path[i]; // Отдельно взятый отрезок по итератору
            for (int j = 0; j < L.size(); ++j) {
                auto [e1, e2, cost] = L[j];
                if (e1 == v1 && e2 == v2 && cost < min)
                    min = cost;
            }
        }
        max_flow += min; // Запоминаем минимальный вес
        for (int i = 1; i < path.size(); ++i) {
            auto [v1, v2] = path[i];
            for (int j = 0; j < L.size(); ++j) {
                auto [e1, e2, cost] = L[j];
                if (e1 == v1 && e2 == v2)
                    L[j] = {e1, e2, cost - min}; // Удаляем ребра в нулевыми весами
            }
        }
        for (int i = 0; i < C.size(); ++i)
            C[i].clear();
        for (auto e : L) {
            auto [v1, v2, flow] = e;
            if (flow > 0)
                C[v1].push_back(v2);
        }
        path = DFS(C, n, v_start, v_stop); // Запоминаем найденный путь
    }
    return max_flow;
}