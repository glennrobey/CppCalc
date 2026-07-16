#pragma once

#include "core/Token.hpp"
#include <string>
#include <vector>

class Tokenizer {
public:
  std::vector<Token> tokenize(const std::string &expression);
};
