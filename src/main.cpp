#include "Parser.hpp"
#include "Tokenizer.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::cout << "C++Calc starting...\n";

  Tokenizer tokenizer;
  std::unordered_map<std::string, double> variables;

  variables["ans"] = 0;

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

      Parser parser(tokens, variables);

      double result = parser.parse();

      variables["ans"] = result;

      std::cout << result << "\n";

    } catch (const std::exception &error) {
      std::cout << "Error: " << error.what() << "\n";
    }
  }

  return 0;
}
