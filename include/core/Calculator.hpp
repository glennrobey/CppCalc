#pragma once

#include "core/History.hpp"
#include "core/Tokenizer.hpp"
#include "core/Variables.hpp"

#include <string>

class Calculator {
public:
  Calculator();

  double evaluate(const std::string &expression);

  void reset();
  void clear();

  const Variables &getVariables() const;
  const History &getHistory() const;

private:
  Tokenizer tokenizer;

  Variables variables;

  History history;
};
