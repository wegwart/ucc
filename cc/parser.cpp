#include "cc.h"
#include <parser.h>
#include <cc_lexer.h>
#include <stdlib.h>

extern FILE* yyin;
extern int yylineno;

IntLiteralExpression::IntLiteralExpression(const char* num_str, int base)
{
    m_num = strtoull(num_str, nullptr, base);
}

ReturnStatement::ReturnStatement(Expression* expr)
{
    m_expr = expr;
}

void yyerror(const char* message)
{
    fprintf(stderr, "line %d: %s\n", yylineno, message);
}

namespace parser {

    void parse(FILE* file)
    {
        yyin = file;
        yyparse();
    }

    

}
