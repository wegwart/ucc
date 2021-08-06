%{
    #include <parser.h>
    #include <stdint.h>

    int yylex();
    void yyerror(const char* message);
%}

%define parse.error verbose

%union {
    char token[128];
    Function* func;
    Statement* stmt;
    StatementList* stmt_list;
}

%token RETURN SIZEOF CONST
%token <token> IDENTIFIER
%type <func> function_declaration
%type <stmt_list> statement_list
%type <stmt> statement

%start declaration_list

%%

declaration_list        : declaration
                        | declaration_list declaration
                        ;

declaration             : function_declaration ';'
                        | function_declaration '{' '}'                  { ($1)->define(); }
                        | function_declaration '{' statement_list '}'   { ($1)->define($3); }
                        ;

function_declaration    : type_ref IDENTIFIER '(' ')'                   { $$ = Function::declare($2); }
                        | type_ref IDENTIFIER '(' arg_list ')'          { $$ = Function::declare($2); }
                        ;

arg_list                : type_ref IDENTIFIER
                        | type_ref IDENTIFIER '[' ']'
                        | arg_list ',' type_ref IDENTIFIER
                        | arg_list ',' type_ref IDENTIFIER '[' ']'
                        ;

type_ref                : IDENTIFIER
                        | CONST IDENTIFIER
                        | type_ref '*'
                        ;

statement_list          : statement                                     { $$ = new StatementList($1); }
                        | statement_list statement                      { $$ = ($1)->add($2); }
                        ;

statement               : ';'                                           { $$ = new EmptyStatement(); }
                        ;

%%
