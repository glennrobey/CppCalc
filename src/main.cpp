#include "Tokenizer.hpp"
#include <iostream>

int main() {
  std::cout << "C++Calc starting...\n";

  Tokenizer tokenizer;

  auto tokens = tokenizer.tokenize("5");

  for (const auto &token : tokens) {
    std::cout << token.getValue() << "\n";
  }

  return 0;
}
