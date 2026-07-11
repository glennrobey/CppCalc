
#pragma once

#include "Token.hpp"
#include <cstddef>
#include <functional>
#include <string>
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
  std::unordered_map<std::string, std::function<double(double)>> functions;
  size_t currentPosition = 0;

  double parseAssignment();
  double parseExpression();
  double parseTerm();
  double parsePower();
  double parseFactor();
};
