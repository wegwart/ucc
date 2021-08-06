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
[a-zA-Z_]+[a-zA-Z0-9_]*     { strcpy(yylval.token, yytext); return IDENTIFIER; }
[ \t\n]                     { }
[!~&+-/%\{\},\(\);\*\[\]]   { return yytext[0]; }
.                           { ECHO; yyerror ("unexpected character"); fprintf(stderr, "%c", yytext[0]); }

%%

int yywrap (void) {return 1;}
