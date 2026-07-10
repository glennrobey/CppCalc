#include "Parser.hpp"
#include <stdexcept>
#include <string>
#include <unordered_map>

Parser::Parser(std::vector<Token> tokens,
               std::unordered_map<std::string, double> &variables)
    : tokens(tokens), variables(variables) {}

double Parser::parse() {
  double result = parseExpression();

  if (currentPosition < tokens.size()) {
    throw std::runtime_error("Unexpected input after calculation");
  }

  return result;
}

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
    } else if (token.getType() == TokenType::Number ||
               token.getType() == TokenType::LeftParen) {
      result *= parseFactor();
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

  if (token.getType() == TokenType::Identifier) {
    currentPosition++;

    if (variables.find(token.getValue()) == variables.end()) {
      throw std::runtime_error("Unknown variable: " + token.getValue());
    }

    return variables[token.getValue()];
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
