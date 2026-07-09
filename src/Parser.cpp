#include "Parser.hpp"
#include <string>

Parser::Parser(std::vector<Token> tokens) { this->tokens = tokens; }

double Parser::parse() { return parseExpression(); }

double Parser::parseExpression() {
  double result = parseTerm();

  while (currentPosition < tokens.size()) {
    Token token = tokens[currentPosition];

    if (token.getType() == TokenType::Plus) {
      currentPosition++;
      result += parseTerm();
    } else if (token.getType() == TokenType::Minus) {
      currentPosition++;
      result -= parseTerm();
    } else {
      break;
    }
  }

  return result;
}

double Parser::parseTerm() { return parseFactor(); }

double Parser::parseFactor() {
  Token token = tokens[currentPosition];

  currentPosition++;

  return std::stod(token.getValue());
}
