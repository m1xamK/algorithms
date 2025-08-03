#include "./KnutMorisPrattAlgoApi.hpp"
#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <climits>
#include <string>


void getPrefixTable(const std::string pattern, std::vector<int>& table);
size_t searchKnuttMorisPratt(const std::string text, const std::string pattern);
size_t searchKnuttMorisPratt(const std::string text, const std::string pattern, std::vector<size_t>& arr);