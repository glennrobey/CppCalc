#include "core/Tokenizer.hpp"
#include <cctype>
#include <string>

std::vector<Token> Tokenizer::tokenize(const std::string &expression) {
  std::vector<Token> tokens;
  std::string numberBuffer;

  for (size_t i = 0; i < expression.size(); i++) {
    char character = expression[i];

    if (std::isspace(character)) {
      continue;
    }

    if (std::isdigit(character) || character == '.') {
      numberBuffer += character;
    } else {
      // Finish any number we were building
      if (!numberBuffer.empty()) {
        tokens.push_back(Token(TokenType::Number, numberBuffer));
        numberBuffer.clear();
      }

      // Variables / identifiers
      if (std::isalpha(character)) {
        std::string identifier;

        while (i < expression.size() &&
               (std::isalnum(expression[i]) || expression[i] == '_')) {
          identifier += expression[i];
          i++;
        }

        i--;

        tokens.push_back(Token(TokenType::Identifier, identifier));
        continue;
      }

      // Operators
      if (character == '+') {
        tokens.push_back(Token(TokenType::Plus, "+"));
      }

      if (character == '-') {
        tokens.push_back(Token(TokenType::Minus, "-"));
      }

      if (character == '*') {
        tokens.push_back(Token(TokenType::Multiply, "*"));
      }

      if (character == '/') {
        tokens.push_back(Token(TokenType::Divide, "/"));
      }

      if (character == '(') {
        tokens.push_back(Token(TokenType::LeftParen, "("));
      }

      if (character == ',') {
        tokens.push_back(Token(TokenType::Comma, ","));
      }

      if (character == ')') {
        tokens.push_back(Token(TokenType::RightParen, ")"));
      }
      if (character == '^') {
        tokens.push_back(Token(TokenType::Power, "^"));
      }

      // Assignment operator
      if (character == '=') {
        tokens.push_back(Token(TokenType::Assignment, "="));
      }
    }
  }

  // Add any number left at the end
  if (!numberBuffer.empty()) {
    tokens.push_back(Token(TokenType::Number, numberBuffer));
  }

  return tokens;
}
