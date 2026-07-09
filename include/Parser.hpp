#pragma once

#include "Token.hpp"
#include <cstddef>
#include <vector>

class Parser {
public:
  Parser(std::vector<Token> tokens);
  double parse();

private:
  std::vector<Token> tokens;
  size_t currentPosition = 0;

  double parseExpression();
  double parseTerm();
  double parseFactor();
};
