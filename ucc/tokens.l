%{
    #include "y.tab.h"
    void yyerror (char *s);
    int yylex();
%}
%%

"return"                    { return RETURN; }
[a-zA-Z_]+[a-zA-Z0-9_]*     { yylval.id = yytext; return IDENTIFIER; }
[0-9]+                      { yylval.num = atoi(yytext); return INT_LITERAL; }
[ \t\n]                     { }
[\{\},\(\);]                { return yytext[0]; }
.                           { ECHO; yyerror ("unexpected character"); fprintf(stderr, "%c", yytext[0]); }

%%

int yywrap (void) {return 1;}