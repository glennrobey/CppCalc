#include "Parser.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

Parser::Parser(std::vector<Token> tokens,
               std::unordered_map<std::string, double> &variables)
    : tokens(tokens), variables(variables) {
  functions["sqrt"] = [](double x) { return std::sqrt(x); };
  functions["sin"] = [](double x) { return std::sin(x); };
  functions["cos"] = [](double x) { return std::cos(x); };
  functions["log"] = [](double x) { return std::log(x); };
}

double Parser::parse() {
  double result = parseAssignment();

  if (currentPosition < tokens.size()) {
    throw std::runtime_error("Unexpected input after calculation");
  }

  return result;
}

double Parser::parseAssignment() {
  if (currentPosition + 1 < tokens.size() &&
      tokens[currentPosition].getType() == TokenType::Identifier &&
      tokens[currentPosition + 1].getType() == TokenType::Assignment) {

    std::string variableName = tokens[currentPosition].getValue();

    currentPosition += 2;

    double value = parseExpression();

    variables[variableName] = value;

    return value;
  }

  return parseExpression();
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
  double result = parsePower();

  while (currentPosition < tokens.size()) {
    Token token = tokens[currentPosition];

    if (token.getType() == TokenType::Multiply) {
      currentPosition++;
      result *= parsePower();
    } else if (token.getType() == TokenType::Divide) {
      currentPosition++;
      double divisor = parsePower();
      if (divisor == 0) {
        throw std::runtime_error("Division by zero");
      }
      result /= divisor;
    } else if (token.getType() == TokenType::Number ||
               token.getType() == TokenType::Identifier ||
               token.getType() == TokenType::LeftParen) {
      result *= parsePower();
    } else {
      break;
    }
  }

  return result;
}

double Parser::parsePower() {
  double result = parseFactor();

  if (currentPosition < tokens.size() &&
      tokens[currentPosition].getType() == TokenType::Power) {
    currentPosition++;

    result = std::pow(result, parsePower());
  }

  return result;
}

double Parser::parseFactor() {
  if (currentPosition >= tokens.size()) {
    throw std::runtime_error("Unexpected end of expression");
  }

  Token token = tokens[currentPosition];

  // Negative numbers
  if (token.getType() == TokenType::Minus) {
    currentPosition++;
    return -parseFactor();
  }

  // Numbers
  if (token.getType() == TokenType::Number) {
    currentPosition++;

    return std::stod(token.getValue());
  }

  // Variables OR Functions
  if (token.getType() == TokenType::Identifier) {
    currentPosition++;

    std::string name = token.getValue();

    // Function call: sqrt(25)
    if (currentPosition < tokens.size() &&
        tokens[currentPosition].getType() == TokenType::LeftParen) {

      currentPosition++;

      double argument = parseExpression();

      if (currentPosition >= tokens.size() ||
          tokens[currentPosition].getType() != TokenType::RightParen) {
        throw std::runtime_error("Missing ')' after function");
      }

      currentPosition++;

      if (functions.find(name) == functions.end()) {
        throw std::runtime_error("Unknown function: " + name);
      }

      return functions[name](argument);
    }

    // Variable lookup: x
    if (variables.find(name) == variables.end()) {
      throw std::runtime_error("Unknown variable: " + name);
    }

    return variables[name];
  }

  // Parentheses
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
