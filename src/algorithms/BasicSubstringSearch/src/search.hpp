#include "./searchApi.hpp"
#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <climits>
#include <string>

size_t searchRabinCarp(std::string pat, std::string txt, int q);
size_t searchRabinCarp(std::string pat, std::string txt, int q, std::vector<size_t>& arr);
void getPrefixTable(const std::string pattern, std::vector<int>& table);
size_t searchKnuttMorisPratt(const std::string text, const std::string pattern);
size_t searchKnuttMorisPratt(const std::string text, const std::string pattern, std::vector<size_t>& arr);
void buildFiniteAutomaton(std::string pattern, int** TF);
size_t finiteAutomatonSearch(std::string text, std::string pattern);
size_t finiteAutomatonSearch(std::string text, std::string pattern, std::vector<size_t>& arr);
size_t searchBoierMur(std::string text, std::string pattern);
size_t searchBoierMur(std::string text, std::string pattern, std::vector<size_t>& arr);