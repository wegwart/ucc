%{
    #include <parser.h>
    #include <stdint.h>

    int yylex();
    void yyerror(const char* message);
%}

%define parse.error verbose

%union {
    char token[128];
    ast::Function* func;
    ast::Statement* stmt;
}

%token RETURN SIZEOF CONST
%token <token> IDENTIFIER
%type <func> function_declaration
%type <stmt> statement statement_list

%start declaration_list

%%

declaration_list        : declaration
                        | declaration_list declaration
                        ;

declaration             : function_declaration ';'
                        | function_declaration '{' '}'                  { ($1)->define(); }
                        | function_declaration '{' statement_list '}'   { ($1)->define($3); }
                        ;

function_declaration    : type_ref IDENTIFIER '(' ')'                   { $$ = ast::Function::declare($2); }
                        | type_ref IDENTIFIER '(' arg_list ')'          { $$ = ast::Function::declare($2); }
                        ;

arg_list                : type_ref IDENTIFIER
                        | arg_list ',' type_ref IDENTIFIER
                        ;

type_ref                : IDENTIFIER
                        | type_ref '*'
                        ;

statement_list          : statement                                     { $$ = new ast::StatementList($1); }
                        | statement_list statement                      { $$ = ((ast::StatementList*)$1)->add($2); }
                        ;

statement               : ';'                                           { $$ = new ast::EmptyStatement(); }
                        ;

%%
