#include <cstdio>

#include "compiler.hpp"

#include "ast.hpp"
#include "vm.hpp"

#include "parser.hpp"

extern int      yyparse();
extern FILE*    yyin;

using namespace vm;

Compiler::Compiler(const std::string& fname)
{
    if (!fname.empty()) {
        yyin = fopen(fname.c_str(), "r");
    }

    yyparse();
}

void Compiler::run()
{
    const Expressions& program = prog();
    for (Expressions::const_iterator exp = program.begin();
         exp != program.end();
         ++exp) {
        Expression* e = *exp;
        e->run();
    }
}

