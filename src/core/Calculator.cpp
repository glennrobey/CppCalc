#include "core/Calculator.hpp"
#include "core/Parser.hpp"

#include <string>

Calculator::Calculator() { initializeVariables(); }

void Calculator::initializeVariables() {
  variables["ans"] = 0;
  variables["pi"] = 3.141592653589793;
  variables["e"] = 2.718281828459045;
}

double Calculator::evaluate(const std::string &expression) {

  auto tokens = tokenizer.tokenize(expression);

  Parser parser(tokens, variables);

  double result = parser.parse();

  variables["ans"] = result;

  history.add(expression, result);

  return result;
}

void Calculator::clearVariables() {
  variables.clear();
  initializeVariables();
}

void Calculator::reset() {
  clearVariables();
  history.clear();
}

const std::unordered_map<std::string, double> &
Calculator::getVariables() const {
  return variables;
}

const History &Calculator::getHistory() const { return history; }
