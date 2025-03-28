%{
#include <stdio.h>
%}

%option noyywrap

%%

[0-9]+    { printf("NUMBER: %s\n", yytext); }
[a-zA-Z]+ { printf("WORD: %s\n", yytext); }
.         { printf("UNKNOWN: %s\n", yytext); }

%%

int main(){
    yylex();
    return 0;
}
