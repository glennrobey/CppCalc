cmake_minimum_required(VERSION 3.20)

project(CppCalc)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Calculator engine
add_library(
    CppCalcCore

    src/core/Calculator.cpp
    src/core/Functions.cpp
    src/core/Parser.cpp
    src/core/Token.cpp
    src/core/Tokenizer.cpp
    src/core/History.cpp
    src/core/Variables.cpp
)


target_include_directories(
    CppCalcCore
    PUBLIC include
)


# CLI program
add_executable(
    C++Calc

    src/cli/main.cpp
    src/cli/Commands.cpp
)


target_link_libraries(
    C++Calc
    PRIVATE CppCalcCore
)


# Tests
add_executable(
    CalculatorTests

    tests/CalculatorTests.cpp
)


target_link_libraries(
    CalculatorTests
    PRIVATE CppCalcCore
)
