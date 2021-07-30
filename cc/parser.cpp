#include "cc.h"

extern "C" {
    #include <ucc_lexer.h>
}

extern FILE* yyin;

namespace parser {

    void parse(FILE* file)
    {
        yyin = file;
        yyparse();
    }

    extern "C" void yyerror(const char* message)
    {
        fprintf(stderr, "%s\n", message);
    }

}