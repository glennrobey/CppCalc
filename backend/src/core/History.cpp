#include "core/History.hpp"

void History::add(const std::string &expression, double result) {
  entries.push_back(expression + " = " + std::to_string(result));
}

void History::clear() { entries.clear(); }

const std::vector<std::string> &History::getEntries() const { return entries; }
