#include "cc.h"

extern "C" {
    #include <cc_lexer.h>
}

extern FILE* yyin;
extern int yylineno;

namespace parser {

    void parse(FILE* file)
    {
        yyin = file;
        yyparse();
    }

    extern "C" void yyerror(const char* message)
    {
        fprintf(stderr, "line %d: %s\n", yylineno, message);
    }

}
