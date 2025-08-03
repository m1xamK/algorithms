#pragma once
#include <vector>
#include <string>

namespace KMP {
    std::vector<int> computePrefixFunction(const std::string& pattern);
    std::vector<int> search(const std::string& text, const std::string& pattern);
}
