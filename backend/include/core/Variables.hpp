#pragma once

#include <string>
#include <unordered_map>

class Variables {
public:
  Variables();

  void set(const std::string &name, double value);

  double get(const std::string &name) const;

  bool exists(const std::string &name) const;

  void clear();

  const std::unordered_map<std::string, double> &getAll() const;

private:
  void initialize();

  std::unordered_map<std::string, double> variables;
};
