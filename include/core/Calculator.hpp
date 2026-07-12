#pragma once

#include "core/History.hpp"
#include "core/Tokenizer.hpp"

#include <string>
#include <unordered_map>

class Calculator {
public:
  Calculator();

  double evaluate(const std::string &expression);

  void reset();
  void clearVariables();

  const std::unordered_map<std::string, double> &getVariables() const;
  const History &getHistory() const;

private:
  void initializeVariables();

  Tokenizer tokenizer;

  std::unordered_map<std::string, double> variables;

  History history;
};
