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

double Parser::parseTerm() {
  double result = parseFactor();

  while (currentPosition < tokens.size()) {
    Token token = tokens[currentPosition];

    if (token.getType() == TokenType::Multiply) {
      currentPosition++;
      result *= parseFactor();
    } else if (token.getType() == TokenType::Divide) {
      currentPosition++;
      result /= parseFactor();
    } else {
      break;
    }
  }

  return result;
}

double Parser::parseFactor() {
  Token token = tokens[currentPosition];

  currentPosition++;

  return std::stod(token.getValue());
}
