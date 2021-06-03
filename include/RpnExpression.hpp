#ifndef SIMPLE_CALCULATOR_RpnExpression_H
#define SIMPLE_CALCULATOR_RpnExpression_H

#include "TokenBase.hpp"

#include <vector>

class RpnExpression {

public:
    void push(TokenBase *t)
    { m_stack.push_back(t); }

    TokenBase* pop() {

        TokenBase *t{ m_stack.front() };
        m_stack.erase(m_stack.begin());
        return t;
    }

    bool empty() const
    { return m_stack.empty(); }

private:
    std::vector<TokenBase*> m_stack;
};

#endif // SIMPLE_CALCULATOR_RpnExpression_H