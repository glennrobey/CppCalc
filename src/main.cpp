#include "Parser.hpp"
#include "Tokenizer.hpp"
#include <cctype>
#include <iostream>
#include <string>

int main() {
  std::cout << "C++Calc starting...\n";

  Tokenizer tokenizer;

  while (true) {
    std::string input;

    std::cout << "> ";

    if (!std::getline(std::cin, input)) {
      break;
    }

    if (input == "exit") {
      break;
    }

    bool onlyWhitespace = true;

    for (char character : input) {
      if (!std::isspace(character)) {
        onlyWhitespace = false;
        break;
      }
    }

    if (onlyWhitespace) {
      std::cout << "Error: Please enter an expression\n";
      continue;
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
