%{
    void yyerror (char *s);
    int yylex();

    #include <stdio.h>
%}

%union { char* id; int num; }
%token <id> IDENTIFIER
%token <num> INT_LITERAL
%token RETURN

%start declaration_list

%%

declaration_list        : declaration
                        | declaration_list declaration
                        ;

declaration             : function_declaration ';'
                        | function_declaration statement
                        ;

function_declaration    : type IDENTIFIER '(' arg_list ')'
                        ;

arg_list                :
                        | type IDENTIFIER
                        | type IDENTIFIER ',' arg_list
                        ;

type                    : IDENTIFIER
                        ;

statement               :
                        | '{' statement '}'
                        | RETURN expression ';'
                        ;

expression              : '(' expression ')'
                        | primary_expression
                        ;

primary_expression      : INT_LITERAL
                        ;

%%

void yyerror(char* s)
{
    fprintf(stderr, "%s\n", s);
}