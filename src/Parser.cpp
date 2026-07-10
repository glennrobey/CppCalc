#include "Parser.hpp"
#include <stdexcept>
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
      double divisor = parseFactor();
      if (divisor == 0) {
        throw std::runtime_error("Division by zero");
      }
      result /= divisor;
    } else {
      break;
    }
  }

  return result;
}

double Parser::parseFactor() {
  if (currentPosition >= tokens.size()) {
    throw std::runtime_error("Unexpected end of expression");
  }
  Token token = tokens[currentPosition];

  if (token.getType() == TokenType::Minus) {
    currentPosition++;
    return -parseFactor();
  }

  if (token.getType() == TokenType::Number) {
    currentPosition++;

    return std::stod(token.getValue());
  }

  if (token.getType() == TokenType::LeftParen) {
    currentPosition++;

    double result = parseExpression();
    if (currentPosition >= tokens.size() ||
        tokens[currentPosition].getType() != TokenType::RightParen) {
      throw std::runtime_error("Missing closing parenthesis");
    }

    currentPosition++;

    return result;
  }

  throw std::runtime_error("Expected a number");
}
