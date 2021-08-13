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
"const"                     { return CONST;  }
0x[0-9a-fA-F]+              { yylval.integer = strtoull(yytext + 2, nullptr, 16); return INT_LITERAL; }
[0-9]+                      { yylval.integer = strtoull(yytext, nullptr, 10); return INT_LITERAL; }
[a-zA-Z_]+[a-zA-Z0-9_]*     { strcpy(yylval.token, yytext); return IDENTIFIER; }
[ \t\n]                     { }
[!~&+-/%\{\},\(\);\*\[\]]   { return yytext[0]; }
.                           { ECHO; yyerror ("unexpected character"); fprintf(stderr, "%c", yytext[0]); }

%%

int yywrap (void) {return 1;}
