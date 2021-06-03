#ifndef SIMPLE_CALCULATOR_ShuntingYard_H
#define SIMPLE_CALCULATOR_ShuntingYard_H

#include "TokenBase.hpp"
#include "RpnExpression.hpp"

#include <map>
#include <stack>
#include <utility>
#include <string>

class ShuntingYard {

public:
    ShuntingYard(const std::string &infix) : m_expression(infix) {
        
        m_op_precedence['('] = -1;
        m_op_precedence['+'] = 2; m_op_precedence['-'] = 2;
        m_op_precedence['*'] = 3; m_op_precedence['/'] = 3;
    }

    RpnExpression to_rpn() { return convert(m_expression); }

private:
    const std::string m_expression;
    std::stack<char> m_op_stack;
    RpnExpression m_rpn;
    mutable std::map<char, int> m_op_precedence;

    int precedence(char op) const { return m_op_precedence[op]; }

    int stack_precedence () const {

        if(m_op_stack.empty()) return -1;
        return precedence(m_op_stack.top());
    }

    void handle_left_paren() { m_op_stack.push('('); }

    void handle_right_paren() {

        while (m_op_stack.top() != '(') {

            m_rpn.push(new Token<char>(m_op_stack.top()));
            m_op_stack.pop();
        }
        m_op_stack.pop();
    }

    void handle_op(char op) {

        while (!m_op_stack.empty() && precedence(op) <= stack_precedence()) {

            m_rpn.push(new Token<char>(m_op_stack.top()));
            m_op_stack.pop();
        }
        m_op_stack.push(op);
    }

    RpnExpression convert(const std::string &infix) {

        auto token = infix.c_str();

        while (token && *token) {

            while (*token && std::isspace(*token)) ++token;

            if (!*token) break;

            if (std::isdigit(*token)) {

                char *next_token{};
                m_rpn.push(new Token<double>(std::strtod(token, &next_token)));
                token = next_token;
            }
            else {

                char op{ *token };

                switch (op) {

                    case '(': {

                        handle_left_paren();
                        break;
                    }
                    case ')': {

                        handle_right_paren();
                        break;
                    }
                    default: {
                        handle_op(op);
                    }
                }

                ++token;
            }
        }

        while (!m_op_stack.empty ()) {

            m_rpn.push(new Token<char>(m_op_stack.top()));
            m_op_stack.pop();
        }

        return m_rpn;
    }

};
 #endif // SIMPLE_CALCULATOR_ShuntingYard_H