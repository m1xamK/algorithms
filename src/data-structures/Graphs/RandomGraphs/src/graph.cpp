#include "../include/graph.h"
#include <random>
#include <queue>
#include <cmath>
#include <sstream>
#include <numeric>
#include <ranges> 
#include <algorithm>
static std::mt19937_64 RNG{ std::random_device{}() };

/*
   ■  Классическая «монетка для каждой пары» вызывает RNG ½·n² раз.
      Для n≥1000 это миллионы вызовов.

   ■  Наблюдение: расстояние до следующего успеха (ребра) распределено
      геометрически:  Pr{Δ=k} = (1-p)^k · p.

   ■  Берём одно U∼Unif(0,1)  и сразу получаем
         Δ = floor( ln U / ln(1-p) ).

      — экономим RNG-вызовы (≈ m, а не n²)  
      — общая сложность O(n + m).
*/
std::vector<Edge> gen_erdos_renyi(int n, double p)
{
    std::uniform_real_distribution<double> U(0.0,1.0);
    const double log1mp = std::log(1.0 - p);

    std::vector<Edge> E;
    E.reserve(static_cast<std::size_t>(p * n * (n-1) / 2));

    for (int u = 0; u < n; ++u)
    {
        int v = u + 1;
        while (v < n)
        {
            int skip = static_cast<int>(std::log(U(RNG)) / log1mp);
            v += skip;
            if (v < n) { E.emplace_back(u,v); ++v; }   // ребро найдено
        }
    }
    return E;
}

// Создание списков смежности
static auto buildAdjacencyLists(int n, const std::vector<Edge>& E)
{
    std::vector<std::vector<int>> g(n);
    for (auto [u,v]: E) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

// поиск в ширину
static std::vector<int> myBFS(int n, const std::vector<std::vector<int>>& g, int src)
{
    std::vector<int> dist(n,-1);
    std::queue<int> q;
    q.push(src);
    dist[src] = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: g[u])
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
    return dist;
}

bool connected(int n, const std::vector<Edge>& E)
{
    auto d = myBFS(n, buildAdjacencyLists(n,E), 0);
    return std::all_of(d.begin(), d.end(), [](int x){ return x != -1; });
}

double avg_path_len(int n, const std::vector<Edge>& E, int samples)
{
    auto g = buildAdjacencyLists(n,E);
    std::uniform_int_distribution<int> pick(0, n-1);
    long long sum = 0, cnt = 0;
    for (int t = 0; t < samples; ++t) {
        auto d = myBFS(n, g, pick(RNG));
        for (int x: d) {
            if(x > 0) {
                sum += x;
                ++cnt;
            }
        }
    }
    return cnt ? double(sum)/cnt : 0.0;
}

std::vector<int> greedy_coloring(int n, const std::vector<Edge>& E)
{
    auto g = buildAdjacencyLists(n, E);
    std::vector<int> col(n, -1), used(n, 0);
    for (int u = 0; u < n; ++u)
    {
        for (int v : g[u])                  // помечаем занятые цвета соседей
            if (col[v] >= 0) used[col[v]] = 1;
        int c = 0;
        while (used[c])
            ++c;                            // ищем первый свободный
        col[u] = c;                       
        for (int v : g[u])                  // снимаем метки
            if (col[v] >= 0) used[col[v]] = 0;
    }
    return col;
}

double edge_resilience(int n, const std::vector<Edge>& E, int k, int repeats)
{
    std::uniform_int_distribution<std::size_t> pick(0, E.size()-1);
    int ok = 0; std::vector<char> gone(E.size());

    for(int r = 0; r < repeats; ++r) {
        std::fill(gone.begin(), gone.end(), 0);
        for (int i=0;i<k;++i) {
            std::size_t id;
            do id=pick(RNG);
            while(gone[id]);
            gone[id]=1;
        }
        std::vector<Edge> sub; sub.reserve(E.size()-k);
        for (std::size_t i = 0; i < E.size(); ++i)
            if (!gone[i])
            sub.push_back(E[i]);
        if(connected(n,sub)) ++ok;
    }
    return double(ok)/repeats;   // вероятность остаться связанным
}


std::string to_dot(int n, const std::vector<Edge>& E, const std::vector<int>* colors = nullptr, const std::string& label  = "")
{
    constexpr double PHI = 0.618033988749895;   // «золотой» шаг по кругу
    std::ostringstream dot;
    dot << "graph G {\n"
        << "  node [style=filled,fontcolor=white];\n";
    if (!label.empty())
        dot << "  label=\"" << label << "\";\n";
    for (int u = 0; u < n; ++u) {
        dot << "  " << u;
        if (colors) {

            /* hue равномерно «размазывается» по кругу (mod 1)  */
            double h = std::fmod((*colors)[u] * PHI, 1.0);  // 0‥1
            double s = 0.65;                                // насыщенность
            double v = 0.95;                                // яркость
            dot << " [fillcolor=\"" << h << ' ' << s << ' ' << v << "\"]";
        }
        dot << ";\n";
    }
    for (auto [u,v] : E)
        dot << "  " << u << " -- " << v << ";\n";
    dot << "}\n";
    return dot.str();
}