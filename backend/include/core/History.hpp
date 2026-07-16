#pragma once

#include <string>
#include <vector>

class History {
public:
  void add(const std::string &expression, double result);

  void clear();

  const std::vector<std::string> &getEntries() const;

private:
  std::vector<std::string> entries;
};
