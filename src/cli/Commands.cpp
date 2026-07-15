#include "cli/Commands.hpp"

#include <exception>
#include <iostream>
#include <string>

Commands::Commands(Calculator &calculator) : calculator(calculator) {}

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

    std::cout << handleCommand(input) << "\n";
  }
}

std::string Commands::handleCommand(const std::string &input) {

  if (input == "help") {
    return printHelp();
  }

  if (input == "vars") {

    std::string output;

    for (const auto &entry : calculator.getVariables().getAll()) {
      output += entry.first + "=" + std::to_string(entry.second) + "\n";
    }

    return output;
  }
  if (input == "history") {

    std::string output;

    for (const auto &entry : calculator.getHistory().getEntries()) {
      output += entry + "\n";
    }

    return output;
  }

  if (input == "clear") {

    calculator.clear();

    return "Variables cleared";
  }

  if (input == "reset") {

    calculator.reset();

    return "Calculator reset";
  }

  try {

    double result = calculator.evaluate(input);

    return std::to_string(result);

  } catch (const std::exception &error) {

    return "Error: " + std::string(error.what());
  }
}

std::string Commands::printHelp() {

  return "Commands:\n"
         "  help      Show this message\n"
         "  vars      Show variables\n"
         "  history   Show calculations\n"
         "  clear     Clear variables\n"
         "  reset     Factory reset calculator\n"
         "  exit      Quit calculator";
}
