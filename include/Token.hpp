#pragma once

#include <string>

enum class TokenType { Number, Plus, Minus, Multiply, Divide };

class Token {
public:
  Token(TokenType type, std::string value);

  TokenType getType() const;
  std::string getValue() const;

private:
  TokenType type;
  std::string value;
};
