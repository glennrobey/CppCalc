#include "core/Token.hpp"

Token::Token(TokenType type, std::string value) {
  this->type = type;
  this->value = value;
}

TokenType Token::getType() const { return type; }

std::string Token::getValue() const { return value; }
