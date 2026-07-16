#include "core/Functions.hpp"

#include <cmath>
#include <stdexcept>

Functions::Functions() {

  functions["sqrt"] = [](std::vector<double> args) {
    if (args.size() != 1)
      throw std::runtime_error("sqrt expects 1 argument");

    if (args[0] < 0)
      throw std::runtime_error("sqrt domain error");

    return std::sqrt(args[0]);
  };

  functions["sin"] = [](std::vector<double> args) {
    if (args.size() != 1)
      throw std::runtime_error("sin expects 1 argument");

    return std::sin(args[0]);
  };

  functions["cos"] = [](std::vector<double> args) {
    if (args.size() != 1)
      throw std::runtime_error("cos expects 1 argument");

    return std::cos(args[0]);
  };

  functions["log"] = [](std::vector<double> args) {
    if (args.size() != 1)
      throw std::runtime_error("log expects 1 argument");

    if (args[0] <= 0)
      throw std::runtime_error("log domain error");

    return std::log(args[0]);
  };

  functions["pow"] = [](std::vector<double> args) {
    if (args.size() != 2)
      throw std::runtime_error("pow expects 2 arguments");

    return std::pow(args[0], args[1]);
  };
}

double Functions::call(const std::string &name,
                       const std::vector<double> &arguments) const {

  if (!exists(name)) {
    throw std::runtime_error("Unknown function: " + name);
  }

  return functions.at(name)(arguments);
}

bool Functions::exists(const std::string &name) const {

  return functions.find(name) != functions.end();
}
