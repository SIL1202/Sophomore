%{
#include<main.h>
%}

%%
[a-zA-Z][0-9a-zA-Z_]*   {return IDENTIFIER;}
-?(0|[1-9][0-9]*)       {return INTEGER;}
[0-9]*\.[0-9]+ | [0-9]+\.[0-9]* { return FLOAT; }
[ \t\n]                 ;
.                       ;
%%

int yywrap(void){
  return 1;
}
