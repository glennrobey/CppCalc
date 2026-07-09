#include "Parser.hpp"
#include "Tokenizer.hpp"
#include <iostream>

int main() {
  std::cout << "C++Calc starting...\n";

  Tokenizer tokenizer;

  auto tokens = tokenizer.tokenize("5+10");

  Parser parser(tokens);

  double result = parser.parse();

  std::cout << result << "\n";

  return 0;
}
