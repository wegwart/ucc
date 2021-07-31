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

%token RETURN SIZEOF
%token <token> INT_LITERAL STR_LITERAL IDENTIFIER
%type <expr> primary_expr postfix_expr unary_expr cast_expr multiplicative_expr additive_expr expression
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
                        | expression                    { }
                        | RETURN expression ';'         { $$ = new ReturnStatement($2); }
                        ;

expression              : additive_expr             { $$ = $1; }
                        ;

additive_expr           : multiplicative_expr                       { $$ = $1; }
                        | additive_expr '+' multiplicative_expr     { $$ = new BinaryExpr(BinaryExpr::Addition, $1, $3); }
                        | additive_expr '-' multiplicative_expr     { $$ = new BinaryExpr(BinaryExpr::Subtraction, $1, $3); }

multiplicative_expr     : cast_expr                             { $$ = $1; }
                        | multiplicative_expr '*' cast_expr     { $$ = new BinaryExpr(BinaryExpr::Multiplication, $1, $3); }
                        | multiplicative_expr '/' cast_expr     { $$ = new BinaryExpr(BinaryExpr::Division, $1, $3); }
                        | multiplicative_expr '%' cast_expr     { $$ = new BinaryExpr(BinaryExpr::Modulo, $1, $3); }
                        ;

cast_expr               : unary_expr                { $$ = $1; }
                        | '(' type ')' cast_expr    { $$ = new CastExpr($4); }
                        ;

unary_expr              : postfix_expr          { $$ = $1; }
                        | '-' postfix_expr      { $$ = new UnaryExpr(UnaryExpr::Negative, $2); }
                        | '+' postfix_expr      { $$ = $2; }
                        | '&' postfix_expr      { $$ = new UnaryExpr(UnaryExpr::AddressOf, $2); }
                        | '*' postfix_expr      { $$ = new UnaryExpr(UnaryExpr::Deref, $2); }
                        | '~' postfix_expr      { $$ = new UnaryExpr(UnaryExpr::Inverting, $2); }
                        | '!' postfix_expr      { $$ = new UnaryExpr(UnaryExpr::Negation, $2); }
                        | SIZEOF unary_expr     { $$ = new UnaryExpr(UnaryExpr::SizeOf, $2); }
                        ;

postfix_expr            : primary_expr          { $$ = $1; }
	                    ;

primary_expr            : INT_LITERAL           { $$ = new IntLiteralExpression($1); }
                        | STR_LITERAL           { $$ = new StrLiteralExpression($1); }
                        | IDENTIFIER            { $$ = new VariableExpression($1); }
                        | '(' primary_expr ')'  { $$ = $2; }
                        ;

%%
