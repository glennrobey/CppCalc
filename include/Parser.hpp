
#pragma once

#include "Token.hpp"
#include <cstddef>
#include <unordered_map>
#include <vector>

class Parser {
public:
  Parser(std::vector<Token> tokens,
         std::unordered_map<std::string, double> &variables);
  double parse();

private:
  std::vector<Token> tokens;
  std::unordered_map<std::string, double> &variables;
  size_t currentPosition = 0;

  double parseExpression();
  double parseTerm();
  double parseFactor();
};
