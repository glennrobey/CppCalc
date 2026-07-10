cmake_minimum_required(VERSION 3.20)

project(CCalc)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    C++Calc
    src/main.cpp
    src/Calculator.cpp
    src/Parser.cpp
    src/Token.cpp
    src/Tokenizer.cpp
    src/History.cpp

)
