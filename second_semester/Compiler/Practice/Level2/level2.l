%{
#include<main.h>
%}

%%

"int"     {return INTTYPE;}
"char"    {return CHARTYPE;}
"float"   {return FLOATTYPE;}

[a-zA-Z_$][a-zA-Z_0-9]+   {return VARIABLE;}
[=]                       {return EQUAL;}

-?(0|[1-9][.]?[0-9]*)     {return VALUE;}
['][ |a-zA-Z][']          {return CHARACTER;}
[;]                       {return SEMICOLON;}

%%

int yywrap(void){
  return 1;
}
