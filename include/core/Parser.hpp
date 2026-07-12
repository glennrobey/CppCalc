#pragma once

#include "core/Functions.hpp"
#include "core/Token.hpp"
#include "core/Variables.hpp"

#include <cstddef>
#include <string>
#include <vector>

class Parser {
public:
  Parser(std::vector<Token> tokens, Variables &variables, Functions &functions);

  double parse();

private:
  std::vector<Token> tokens;

  Variables &variables;

  Functions &functions;

  size_t currentPosition = 0;

  double parseAssignment();
  double parseExpression();
  double parseTerm();
  double parsePower();
  double parseFactor();
};
