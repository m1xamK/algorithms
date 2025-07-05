#include "./FiniteAutomatAlgoApi.hpp"
#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <climits>
#include <string>


void buildFiniteAutomaton(std::string pattern, int** TF);
size_t finiteAutomatonSearch(std::string text, std::string pattern);
size_t finiteAutomatonSearch(std::string text, std::string pattern, std::vector<size_t>& arr);