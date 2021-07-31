%{
    #include <parser.h>
    #include <cc_lexer.h>
    void yyerror (const char *s);
    int yylex();
%}

%option yylineno

%%

"sizeof"                    { return SIZEOF; }
"return"                    { return RETURN; }
\"[^\n\"]*\"                { yylval.token = yytext; return STR_LITERAL; }
[a-zA-Z_]+[a-zA-Z0-9_]*     { yylval.token = yytext; return IDENTIFIER; }
[0-9]+                      { yylval.token = yytext; return INT_LITERAL; }
[ \t\n]                     { }
[!~&+-/%\{\},\(\);\*]          { return yytext[0]; }
.                           { ECHO; yyerror ("unexpected character"); fprintf(stderr, "%c", yytext[0]); }

%%

int yywrap (void) {return 1;}
