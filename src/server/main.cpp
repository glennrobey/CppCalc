#include "core/Calculator.hpp"

#include <iostream>
#include <string>

int main() {

  Calculator calculator;

  std::cout << "C++Calc server starting...\n";

  std::string expression;

  while (std::getline(std::cin, expression)) {

    try {

      double result = calculator.evaluate(expression);

      std::cout << result << "\n";

    } catch (const std::exception &error) {

      std::cout << "Error: " << error.what() << "\n";
    }
  }

  return 0;
}
