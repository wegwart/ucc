%{
    #include <parser.h>
    #include <stdint.h>

    int yylex();
    void yyerror(const char* message);
%}

%define parse.error verbose

%union {
    char token[128];
    size_t ast_object;
}

%token RETURN SIZEOF CONST
%token <token> IDENTIFIER
%type <ast_object> function_declaration statement statement_list

%start declaration_list

%%

declaration_list        : declaration
                        | declaration_list declaration
                        ;

declaration             : function_declaration ';'
                        | function_declaration '{' '}'                  { AST_ADD_TOP(FunctionDefinition, $1, AST_ADD(EmptyStatement)); }
                        | function_declaration '{' statement_list '}'   { AST_ADD_TOP(FunctionDefinition, $1, $3); }
                        ;

function_declaration    : type_ref IDENTIFIER '(' ')'                   { $$ = AST_ADD_TOP(FunctionDeclaration, $2); }
                        | type_ref IDENTIFIER '(' arg_list ')'          { $$ = AST_ADD_TOP(FunctionDeclaration, $2); }
                        ;

arg_list                : type_ref IDENTIFIER
                        | arg_list ',' type_ref IDENTIFIER
                        ;

type_ref                : IDENTIFIER
                        | type_ref '*'
                        ;

statement_list          : statement                                     { $$ = AST_ADD(StatementList, $1); }
                        | statement_list statement                      { $$ = AST_FIND(StatementList, $1)->add($2); }
                        ;

statement               : ';'                                           { $$ = AST_ADD(EmptyStatement); }
                        ;

%%
