#include "Parser.hpp"
#include "Tokenizer.hpp"
#include <iostream>
#include <string>

int main() {
  std::cout << "C++Calc starting...\n";

  Tokenizer tokenizer;

  while (true) {
    std::string input;

    std::cout << "> ";
    std::getline(std::cin, input);

    if (input == "exit") {
      break;
    }
    auto tokens = tokenizer.tokenize(input);
    Parser parser(tokens);
    double result = parser.parse();
    std::cout << result << "\n";
  }
  return 0;
}
