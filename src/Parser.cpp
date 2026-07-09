#include "Parser.hpp"
#include <string>

Parser::Parser(std::vector<Token> tokens) { this->tokens = tokens; }

double Parser::parse() { return parseExpression(); }

double Parser::parseExpression() { return parseFactor(); }

double Parser::parseFactor() {
  Token token = tokens[currentPosition];

  currentPosition++;

  return std::stod(token.getValue());
}
