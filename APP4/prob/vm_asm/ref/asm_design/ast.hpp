#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <iostream>
#include <array>
#include <unordered_map>

#include "vm.hpp"

//#include "parser.hpp"

//extern int yyparse();

namespace vm
{
    enum Instruction
    {
        ADD,
        SUB,
        MUL,
        DIV,
        LDA,
        STO,
        LDC
    };

    struct Expression
    {
        virtual void run();
    };

    struct Exp_2R: public Expression
    {
        Register r1_;
        Register r2_;
      
        Exp_2R(Register r1, Register r2);
    };

    struct Exp_ADD: public Exp_2R
    {
        Exp_ADD(Register r1, Register r2);

        void run();
    };

    struct Exp_SUB: public Exp_2R
    {
        Exp_SUB(Register r1, Register r2);

        void run();
    };

    struct Exp_MUL: public Exp_2R
    {
        Exp_MUL(Register r1, Register r2);

        void run();
    };

    struct Exp_DIV: public Exp_2R
    {
        Exp_DIV(Register r1, Register r2);

        void run();
    };

    struct Exp_LDA: public Expression
    {
        Register    r1_;
        std::string addr_;

        Exp_LDA(Register r1, const std::string& addr);

        void run();
    };

    struct Exp_STO: public Expression
    {
        std::string addr_;
        Register    r1_;

        Exp_STO(const std::string& addr, Register r1);

        void run();
    };

    struct Exp_LDC: public Expression
    {
        Register    r1_;
        float       val_;

        Exp_LDC(Register r1, float val);

        void run();
    };

    typedef std::vector<Expression*> Expressions;
    Expressions& prog(); // returns a pointer to the current program (expressions).

}

#endif
