#include "core/Parser.hpp"
#include "core/Tokenizer.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void initializeVariables(std::unordered_map<std::string, double> &variables) {
  variables["ans"] = 0;
  variables["pi"] = 3.141592653589793;
  variables["e"] = 2.718281828459045;
}

int main() {
  std::cout << "C++Calc starting...\n";

  Tokenizer tokenizer;
  std::unordered_map<std::string, double> variables;
  std::vector<std::string> history;

  initializeVariables(variables);
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

    if (input == "vars") {
      for (const auto &entry : variables) {
        std::cout << entry.first << "=" << entry.second << "\n";
      }
      continue;
    }

    if (input == "clear") {
      variables.clear();

      initializeVariables(variables);

      std::cout << "Variables cleared\n";
      continue;
    }

    if (input == "reset") {
      variables.clear();
      history.clear();

      initializeVariables(variables);

      std::cout << "Calculator reset\n";
      continue;
    }

    if (input == "help") {
      std::cout << "Commands:\n";
      std::cout << "  help      Show this message\n";
      std::cout << "  vars      Show variables\n";
      std::cout << "  history   Show calculations\n";
      std::cout << "  clear     Clear variables\n";
      std::cout << "  reset     Factory reset calculator\n";
      std::cout << "  exit      Quit calculator\n";
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
