#pragma once

#include "core/Calculator.hpp"

class Commands {
public:
  Commands();

  void run();

private:
  Calculator calculator;

  void printHelp();
  void handleCommand(const std::string &input);
};
