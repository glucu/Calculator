#ifndef SIMPLE_CALCULATOR_Calculator_H
#define SIMPLE_CALCULATOR_Calculator_H

#include "ShuntingYard.hpp"
#include "RpnExpression.hpp"
#include "TokenBase.hpp"

#include <stack>
#include <string>
#include <stdexcept>

class Calculator {

protected:
    void consume(double value) { push(value); }

    void consume(char op) {

        switch (op) {

            case '*': {

                push(pop() * pop());
                break;
            }
            case '/': {

                double right{ pop() };
                if(right == 0) throw std::runtime_error{"divide by zero."};
                push(pop() / right);
                break;
            }
            case '+': {

                push(pop() + pop());
                break;
            }
            case '-': {
                double right{ pop() };
                push(pop() - right );
                break;

            }
            default: {

                throw std::domain_error("Unknown Operator");
            }
        }
    }

public:
    double calculate(const std::string &expr) {

        ShuntingYard shunting{ expr };
        RpnExpression rpn{ shunting.to_rpn() };
        flush();

        while (!rpn.empty()) {

            TokenBase *token{ rpn.pop() };
            token->evaluate(this);
            delete token;
        }
        return result();
    }

    template<typename T> friend class Token;

private:
    std::stack<double> m_operands;

    double pop() {

        double d{ m_operands.top() };
        m_operands.pop();
        return d;
    }

    void push(double d) { m_operands.push(d); }

    double result() const { return m_operands.top(); }

    void flush() {

        while (!m_operands.empty()) {

            m_operands.pop();
        }
    }
};

template<typename T> void Token<T>::evaluate(Calculator *c) { c->consume(token); }

#endif // SIMPLE_CALCULATOR_Calculator_H