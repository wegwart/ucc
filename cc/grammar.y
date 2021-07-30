%{
    int yylex();
    void yyerror(const char* message);
%}

%define parse.error verbose

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

statement_list          : statement
                        | statement_list statement
                        ;

statement               : ';'
                        | '{' statement_list '}'
                        | RETURN expression ';'
                        ;

expression              : '(' expression ')'
                        | primary_expression
                        ;

primary_expression      : INT_LITERAL
                        ;

%%
