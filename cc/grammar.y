%{
    #include <parser.h>
    #include <stdint.h>

    int yylex();
    void yyerror(const char* message);
%}

%define parse.error verbose

%union {
    const char* token;
    Expression* expr;
    Statement* stmt;
}

%token RETURN
%token <token> INT_LITERAL IDENTIFIER
%type <expr> primary_expression expression
%type <stmt> statement statement_list

%start declaration_list

%%

declaration_list        : declaration
                        | declaration_list declaration
                        ;

declaration             : function_declaration ';'
                        | function_declaration '{' '}'
                        | function_declaration '{' statement_list '}'
                        ;

function_declaration    : type IDENTIFIER '(' arg_list ')'
                        ;

arg_list                :
                        | type IDENTIFIER
                        | type IDENTIFIER ',' arg_list
                        ;

type                    : IDENTIFIER
                        | type '*'
                        ;

statement_list          : statement                     { ; }
                        | statement_list statement      { ; }
                        ;

statement               : ';'                           { $$ = new EmptyStatement(); }
                        | '{' statement_list '}'        { $$ = $2; }
                        | RETURN expression ';'         { $$ = new ReturnStatement($2); }
                        ;

expression              : '(' expression ')'            { $$ = $2; }
                        | primary_expression            { $$ = $1; }
                        ;

primary_expression      : INT_LITERAL                   { $$ = new IntLiteralExpression($1); }
                        | IDENTIFIER                    { $$ = new VariableExpression($1); }
                        | '(' primary_expression ')'    { $$ = $2; }
                        ;

%%
