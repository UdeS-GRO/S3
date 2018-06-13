
%{

#include <iostream>
#include <string>
#include "ast.hpp"

extern int yylex();

void yyerror(const char* err)
{
    std::cerr << "Error: " << err << std::endl;
}

using namespace vm;

%}


%union {
    vm::Expressions*    exprs;
    vm::Expression*     expr;
    vm::Instruction     ins;
    vm::Register        reg;
    std::string*        string;
    std::string*        addr;
    float               cons;
}


%token  <token> TOP_ADD;
%token  <token> TOP_SUB;
%token  <token> TOP_MUL;
%token  <token> TOP_DIV;
%token  <token> TOP_LDA;
%token  <token> TOP_STO;
%token  <token> TOP_LDC;
%token  <token> TCOMMA;
%token  <token> TREG;
%token  <addr>  TADDR;
%token  <cons>  TCONS;
%token  <token> TEOL;

%type   <expr>  expr;
%type   <exprs> exprs;
// %type   <reg>   reg;

%%

exprs   : expr  TEOL        { $$ = &prog(); $$->push_back($<expr>1); }
        | exprs expr TEOL   { $1->push_back($<expr>2); }
        ;

expr    : TOP_ADD TREG  TCOMMA TREG     { $$ = new Exp_ADD($<reg>2, $<reg>4); }
        | TOP_SUB TREG  TCOMMA TREG     { $$ = new Exp_SUB($<reg>2, $<reg>4); }
        | TOP_MUL TREG  TCOMMA TREG     { $$ = new Exp_MUL($<reg>2, $<reg>4); }
        | TOP_DIV TREG  TCOMMA TREG     { $$ = new Exp_DIV($<reg>2, $<reg>4); }
        | TOP_LDA TREG  TCOMMA TADDR    { $$ = new Exp_LDA($<reg>2, *$<addr>4); }
        | TOP_STO TADDR TCOMMA TREG     { $$ = new Exp_STO(*$<addr>2, $<reg>4); }
        | TOP_LDC TREG  TCOMMA TCONS    { $$ = new Exp_LDC($<reg>2, $<cons>4); }
        ;

empty   : TEOL {} ;

//reg     : TREG;
//addr    : TADDR;
//cpns    : TCONS;

%%
