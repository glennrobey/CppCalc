#include "Tokenizer.hpp"
#include <cctype>

std::vector<Token> Tokenizer::tokenize(const std::string &expression) {
  std::vector<Token> tokens;

  for (char character : expression) {
    if (isdigit(character)) {
      tokens.push_back(Token(TokenType::Number, std::string(1, character)));
    }
  }

  return tokens;
}
