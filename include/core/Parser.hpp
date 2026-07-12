#pragma once

#include "core/Token.hpp"
#include "core/Variables.hpp"

#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class Parser {
public:
  Parser(std::vector<Token> tokens, Variables &variables);

  double parse();

private:
  std::vector<Token> tokens;

  Variables &variables;

  std::unordered_map<std::string, std::function<double(std::vector<double>)>>
      functions;

  size_t currentPosition = 0;

  double parseAssignment();
  double parseExpression();
  double parseTerm();
  double parsePower();
  double parseFactor();
};
