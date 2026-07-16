#include "core/Variables.hpp"

#include <stdexcept>

Variables::Variables() { initialize(); }

void Variables::initialize() {
  variables["ans"] = 0;
  variables["pi"] = 3.141592653589793;
  variables["e"] = 2.718281828459045;
}

void Variables::set(const std::string &name, double value) {
  variables[name] = value;
}

double Variables::get(const std::string &name) const {

  if (!exists(name)) {
    throw std::runtime_error("Unknown variable: " + name);
  }

  return variables.at(name);
}

bool Variables::exists(const std::string &name) const {
  return variables.find(name) != variables.end();
}

void Variables::clear() {
  variables.clear();
  initialize();
}

const std::unordered_map<std::string, double> &Variables::getAll() const {
  return variables;
}
