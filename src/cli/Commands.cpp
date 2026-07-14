#include "cli/Commands.hpp"

#include <cctype>
#include <exception>
#include <iostream>
#include <string>

Commands::Commands() = default;

void Commands::run() {

  std::cout << "C++Calc starting...\n";

  while (true) {

    std::string input;

    std::cout << "> ";

    if (!std::getline(std::cin, input)) {
      break;
    }

    if (input == "exit") {
      break;
    }

    handleCommand(input);
  }
}

void Commands::handleCommand(const std::string &input) {

  if (input == "help") {
    printHelp();
    return;
  }

  if (input == "vars") {

    for (const auto &entry : calculator.getVariables().getAll()) {
      std::cout << entry.first << "=" << entry.second << "\n";
    }

    return;
  }

  if (input == "history") {

    for (const auto &entry : calculator.getHistory().getEntries()) {
      std::cout << entry << "\n";
    }

    return;
  }

  if (input == "clear") {

    calculator.clear();

    std::cout << "Variables cleared\n";

    return;
  }

  if (input == "reset") {

    calculator.reset();

    std::cout << "Calculator reset\n";

    return;
  }

  try {

    double result = calculator.evaluate(input);

    std::cout << result << "\n";

  } catch (const std::exception &error) {

    std::cout << "Error: " << error.what() << "\n";
  }
}

void Commands::printHelp() {

  std::cout << "Commands:\n";
  std::cout << "  help      Show this message\n";
  std::cout << "  vars      Show variables\n";
  std::cout << "  history   Show calculations\n";
  std::cout << "  clear     Clear variables\n";
  std::cout << "  reset     Factory reset calculator\n";
  std::cout << "  exit      Quit calculator\n";
}
