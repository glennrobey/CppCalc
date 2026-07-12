#include "core/Calculator.hpp"
#include "core/Parser.hpp"

#include <string>

Calculator::Calculator() = default;

double Calculator::evaluate(const std::string &expression) {

  auto tokens = tokenizer.tokenize(expression);

  Parser parser(tokens, variables);

  double result = parser.parse();

  variables.set("ans", result);

  history.add(expression, result);

  return result;
}

void Calculator::clear() { variables.clear(); }

void Calculator::reset() {
  variables.clear();
  history.clear();
}

const Variables &Calculator::getVariables() const { return variables; }

const History &Calculator::getHistory() const { return history; }
