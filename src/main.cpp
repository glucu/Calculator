#include "../include/Calculator.hpp"

#include <iostream>
#include <limits>
#include <algorithm>

const std::string kPrompt{"> "};
const std::string kResult{"= "};
const std::string kQuit{"|"};
const std::string kHelp{"h"};

void print_help() {

    std::cout << "***********************************************" << '\n';
    std::cout << "Available operators: *, /, +, -" << '\n';
    std::cout << "How to kQuit: Press the '|' (pipe) character" << '\n';
    std::cout << "***********************************************" << '\n';
}

void ignoreLine() {

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void calculate() {

    Calculator calculator{};

    while(true) {

        try {

            std::cout << kPrompt;
            std::string expression;
            while(std::cin >> expression) {
                
                expression.erase(std::remove_if(expression.begin(), expression.end(), isspace), expression.end());

                if(expression == kQuit) return;
                if(expression == kHelp) {

                    print_help();
                    std::cin.clear();
                    ignoreLine();
                    std::cout << kPrompt;
                }
                else {

                    std::cout << expression << ' ' << kResult << calculator.calculate(expression) << '\n';
                }
            }
        }
        catch(const std::exception &e) {

            std::cerr << "exception: " << e.what() << '\n';
        }
    }
}

int main() {

    try {
        
        std::cout << "**********************************************************" << '\n';
	    std::cout << "Welcome to my simple calculator. Press H for instructions."  << '\n';
	    std::cout << "**********************************************************" << '\n';

        calculate();

        return 0;
    }
    catch (const std::exception& e) {

        std::cerr << "Exception: " << e.what() << '\n';
        return 1;
    }
    catch (...) {

        std::cerr << "Exception: something went wrong\n";
        return 2;
    }
}