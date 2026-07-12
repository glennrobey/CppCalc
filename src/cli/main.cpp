#include "core/Calculator.hpp"

#include <cctype>
#include <exception>
#include <iostream>
#include <string>

int main() {
  std::cout << "C++Calc starting...\n";

  Calculator calculator;

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
      for (const auto &entry : calculator.getHistory().getEntries()) {
        std::cout << entry << "\n";
      }
      continue;
    }
    if (input == "vars") {
      for (const auto &entry : calculator.getVariables().getAll()) {
        std::cout << entry.first << "=" << entry.second << "\n";
      }
      continue;
    }

    if (input == "clear") {

      calculator.clear();

      std::cout << "Variables cleared\n";
      continue;
    }

    if (input == "reset") {

      calculator.reset();

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

      double result = calculator.evaluate(input);

      std::cout << result << "\n";

    } catch (const std::exception &error) {
      std::cout << "Error: " << error.what() << "\n";
    }
  }

  return 0;
}
