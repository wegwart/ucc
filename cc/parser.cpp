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

StrLiteralExpression::StrLiteralExpression(const char* str)
{
    // TODO: remove '"' characters
    m_str = str;
}

VariableExpression::VariableExpression(const char* variable_name)
{
    m_varname = variable_name;
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
