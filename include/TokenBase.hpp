#ifndef SIMPLE_CALCULATOR_TokenBase_H
#define SIMPLE_CALCULATOR_TokenBase_H

class Calculator;

class TokenBase {

public:
    virtual void evaluate(Calculator *) = 0;
    virtual ~TokenBase() { }
};

template <typename T> class Token : public TokenBase {

public:
    virtual void evaluate (Calculator *c) override;

    Token (T t) : token(t) { }

private:
    T token;

}; 

#endif // SIMPLE_CALCULATOR_TokenBase_H