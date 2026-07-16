#pragma once

#include "core/Calculator.hpp"

#include <string>

class Commands {
public:
  Commands(Calculator &calculator);

  void run();

  std::string handleCommand(const std::string &input);

private:
  Calculator &calculator;

  std::string printHelp();
};
