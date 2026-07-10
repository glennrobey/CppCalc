#include "Tokenizer.hpp"
#include <cctype>

std::vector<Token> Tokenizer::tokenize(const std::string &expression) {
  std::vector<Token> tokens;
  std::string numberBuffer;

  for (char character : expression) {
    if (isdigit(character)) {
      numberBuffer += character;
    } else {
      if (!numberBuffer.empty()) {
        tokens.push_back(Token(TokenType::Number, numberBuffer));
        numberBuffer.clear();
      }

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

      if (character == ')') {
        tokens.push_back(Token(TokenType::RightParen, ")"));
      }
    }
  }

  if (!numberBuffer.empty()) {
    tokens.push_back(Token(TokenType::Number, numberBuffer));
  }

  return tokens;
}
