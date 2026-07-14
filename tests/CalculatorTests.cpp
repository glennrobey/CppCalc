#include "core/Calculator.hpp"

#include <cassert>
#include <iostream>

int main() {

  Calculator calc;

  assert(calc.evaluate("2+2") == 4);
  assert(calc.evaluate("5*6") == 30);
  assert(calc.evaluate("2^8") == 256);

  calc.evaluate("x=10");
  assert(calc.evaluate("x") == 10);

  assert(calc.evaluate("sqrt(25)") == 5);

  calc.evaluate("a=4");
  calc.evaluate("b=6");
  assert(calc.evaluate("a+b") == 10);

  assert(calc.evaluate("2+3*4") == 14);
  assert(calc.evaluate("(2+3)*4") == 20);
  assert(calc.evaluate("2*(3+4)") == 14);

  assert(calc.evaluate("-5") == -5);
  assert(calc.evaluate("-5+10") == 5);
  assert(calc.evaluate("5*-2") == -10);

  assert(calc.evaluate("2(3+4)") == 14);
  assert(calc.evaluate("2pi") == 2 * 3.141592653589793);

  assert(calc.evaluate("ans") == 2 * 3.141592653589793);

  bool threw = false;

  try {
    calc.evaluate("pi=5");
  } catch (...) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    calc.evaluate("e=10");
  } catch (...) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    calc.evaluate("5/0");
  } catch (...) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    calc.evaluate("xyz");
  } catch (...) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    calc.evaluate("sqrt(-1)");
  } catch (...) {
    threw = true;
  }

  assert(threw);

  threw = false;

  try {
    calc.evaluate("(2+3");
  } catch (...) {
    threw = true;
  }

  assert(threw);

  std::cout << "All tests passed!\n";

  return 0;
}
