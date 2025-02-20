#include "PageRank.h"
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <string.h>
#include <sstream>
#include <string>

#define _CRT_SECURE_NO_WARNINGS

#define alpha 0.85

struct Page {
    std::string name;
    std::size_t name_hash;
    std::unordered_set<std::size_t> links;
};

std::vector<Page> parse_csv(const std::string& path) {
    std::ifstream file(path);
    auto hash = std::hash<std::string>{};
    std::vector<Page> pages;
    std::string null;
    std::getline(file, null);
    for (std::string row; std::getline(file, row); ) {
        Page page;
        page.name = strtok(row.data(), ",\n\r");
        page.name_hash = hash(page.name);
        char* link = NULL;
        while (link = strtok(NULL, ",\n\r"))
            if (strcmp(link, "")) {
                std::string name = link;
                page.links.insert(hash(name));
            }
            else break;
        pages.emplace_back(page);
    }

    return pages;
}

std::vector<std::pair<double, std::string>> getPageRank(const std::string& csv_file) {
    std::vector<Page> data = parse_csv(csv_file);
    std::size_t N = data.size();
    double** H = new double* [N];
    for (int i = 0; i < N; ++i)
        H[i] = new double[N] {};
    std::unordered_set<int> columns;
    for (int i = 0; i < N; ++i)
        if (data[i].links.empty())
            columns.insert(i);
    std::vector<std::pair<int, int>> cells;
    for (int i = 0; i < N; ++i)
        for (int j = 0; i < N; ++i) {
            if (data[j].links.find(data[i].name_hash)  != data[j].links.end()) {
                H[i][j] = 1.0 / data[j].links.size();
                cells.emplace_back(i, j);
            }
        }
    double* I = new double[N] {};
    I[0] = 1;
    double prev = 1;
    double eps = 0.0001;
    for (int k = 0; k < 100; ++k) {
        double val = 0;
        for (int i = 0; i < N; ++i)
            val += I[i];
        double sum = 0;
        for (int i : columns)
            sum += I[i];
        sum /= N;

        double* HI = new double[N] {};
        for (auto cell : cells) {
            HI[cell.first] += H[cell.first][cell.second] * I[cell.second];
        }
        for (int i = 0; i < N; ++i) {
            I[i] = alpha * (HI[i] + sum) + (1 - alpha) / N * val;
        }
        delete HI;
        if (std::abs(I[0] - prev) < eps)
            break;
        else
            prev = I[0];
    }
    std::vector<std::pair<double, std::string>> vec;
    for (int i = 0; i < data.size(); ++i)
        vec.emplace_back(I[i], data[i].name);
    delete[] H;
    return vec;
}
   

