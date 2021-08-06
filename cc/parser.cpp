#include "cc.h"
#include <parser.h>
#include <cc_lexer.h>
#include <stdlib.h>

extern FILE* yyin;
extern int yylineno;

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
