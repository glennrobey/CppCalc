cmake_minimum_required(VERSION 3.20)

project(CppCalc)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    C++Calc
    src/cli/main.cpp
    src/core/Calculator.cpp
    src/core/Functions.cpp
    src/core/Parser.cpp
    src/core/Token.cpp
    src/core/Tokenizer.cpp
    src/core/History.cpp
    src/core/Variables.cpp
)

target_include_directories(C++Calc PRIVATE include)

add_executable(
    CalculatorTests
    tests/CalculatorTests.cpp
    src/core/Calculator.cpp
    src/core/Functions.cpp
    src/core/Parser.cpp
    src/core/Token.cpp
    src/core/Tokenizer.cpp
    src/core/History.cpp
    src/core/Variables.cpp
)

target_include_directories(CalculatorTests PRIVATE include)
