#pragma once

#include "core/Tokenizer.hpp"

#include <string>
#include <unordered_map>
#include <vector>

class Calculator {
public:
  Calculator();

  double evaluate(const std::string &expression);

  void reset();
  void clearVariables();

  const std::unordered_map<std::string, double> &getVariables() const;
  const std::vector<std::string> &getHistory() const;

private:
  void initializeVariables();

  Tokenizer tokenizer;

  std::unordered_map<std::string, double> variables;
  std::vector<std::string> history;
};
