cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(Simple_Calculator LANGUAGES CXX)

include_directories(src)

add_executable(Simple_Calculator
        src/Calculator.hpp
        src/main.cpp
        src/RpnExpression.hpp
        src/ShuntingYard.hpp
        src/TokenBase.hpp src/Calc.h)
