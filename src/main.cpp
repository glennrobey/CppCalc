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

    try {
      auto tokens = tokenizer.tokenize(input);

      Parser parser(tokens);

      double result = parser.parse();

      std::cout << result << "\n";
    } catch (const std::exception &error) {
      std::cout << "Error: " << error.what() << "\n";
    }
  }

  return 0;
}
