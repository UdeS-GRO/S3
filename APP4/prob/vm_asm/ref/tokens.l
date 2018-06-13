%{

#include <string>
#include "vm.hpp"
#include "ast.hpp"
#include "parser.hpp"

extern "C" int yywrap()
{
    return 1; // Stop at EOF.
}

using namespace vm;

%}

%option nounput

%%
[ \t]                   ;
\n+                     return TEOL;
ADD                     return TOP_ADD;
SUB                     return TOP_SUB;
MUL                     return TOP_MUL;
DIV                     return TOP_DIV;
LDA                     return TOP_LDA;
STO                     return TOP_STO;
LDC                     return TOP_LDC;
","                     return TCOMMA;
R[1-4]                  yylval.reg = (Register)(atoi(&yytext[1]) - 1); return TREG;
\$[a-zA-Z0-9_]+         yylval.addr = new std::string(&yytext[1]); return TADDR;
-?[0-9]+\.[0-9]+          yylval.cons = atof(yytext); return TCONS;
#.*                     ;
^#.*\n+                 ;
%%
