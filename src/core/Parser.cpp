#include "core/Parser.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

Parser::Parser(std::vector<Token> tokens, Variables &variables)
    : tokens(tokens), variables(variables) {

  functions["sqrt"] = [](std::vector<double> args) {
    if (args.size() != 1)
      throw std::runtime_error("sqrt expects 1 argument");

    if (args[0] < 0)
      throw std::runtime_error("sqrt domain error");

    return std::sqrt(args[0]);
  };

  functions["sin"] = [](std::vector<double> args) {
    if (args.size() != 1)
      throw std::runtime_error("sin expects 1 argument");

    return std::sin(args[0]);
  };

  functions["cos"] = [](std::vector<double> args) {
    if (args.size() != 1)
      throw std::runtime_error("cos expects 1 argument");

    return std::cos(args[0]);
  };

  functions["log"] = [](std::vector<double> args) {
    if (args.size() != 1)
      throw std::runtime_error("log expects 1 argument");

    if (args[0] <= 0)
      throw std::runtime_error("log domain error");

    return std::log(args[0]);
  };

  functions["pow"] = [](std::vector<double> args) {
    if (args.size() != 2)
      throw std::runtime_error("pow expects 2 arguments");

    return std::pow(args[0], args[1]);
  };
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

    if (variableName == "pi" || variableName == "e") {
      throw std::runtime_error("Cannot overwrite constant: " + variableName);
    }

    currentPosition += 2;

    double value = parseExpression();

    variables.set(variableName, value);

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

    // Function call: sqrt(25), pow(2,8)
    if (currentPosition < tokens.size() &&
        tokens[currentPosition].getType() == TokenType::LeftParen) {

      currentPosition++;

      std::vector<double> arguments;

      while (true) {

        arguments.push_back(parseExpression());

        if (currentPosition < tokens.size() &&
            tokens[currentPosition].getType() == TokenType::Comma) {

          currentPosition++;
          continue;
        }

        break;
      }

      if (currentPosition >= tokens.size() ||
          tokens[currentPosition].getType() != TokenType::RightParen) {

        throw std::runtime_error("Missing ')' after function");
      }

      currentPosition++;

      if (functions.find(name) == functions.end()) {
        throw std::runtime_error("Unknown function: " + name);
      }

      return functions[name](arguments);
    }

    // Variable lookup
    return variables.get(name);
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
