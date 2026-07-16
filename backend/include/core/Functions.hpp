#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class Functions {
public:
  Functions();

  double call(const std::string &name,
              const std::vector<double> &arguments) const;

  bool exists(const std::string &name) const;

private:
  std::unordered_map<std::string, std::function<double(std::vector<double>)>>
      functions;
};
