#include "Parser.hpp"
#include "Tokenizer.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  std::cout << "C++Calc starting...\n";

  Tokenizer tokenizer;
  std::unordered_map<std::string, double> variables;
  std::vector<std::string> history;

  variables["ans"] = 0;
  variables["pi"] = 3.141592653589793;
  variables["e"] = 2.718281828459045;

  while (true) {
    std::string input;

    std::cout << "> ";

    if (!std::getline(std::cin, input)) {
      break;
    }

    if (input == "exit") {
      break;
    }

    if (input == "history") {
      for (const auto &entry : history) {
        std::cout << entry << "\n";
      }
      continue;
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

      history.push_back(input + " = " + std::to_string(result));

      std::cout << result << "\n";

    } catch (const std::exception &error) {
      std::cout << "Error: " << error.what() << "\n";
    }
  }

  return 0;
}
