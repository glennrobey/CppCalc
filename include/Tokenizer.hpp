#pragma once

#include "Token.hpp"
#include <string>
#include <vector>

class Tokenizer {
public:
  std::vector<Token> tokenize(const std::string &expression);
};
