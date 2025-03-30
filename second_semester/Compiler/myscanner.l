%{
#include <myscanner.h>
%}

%%
:               return COLON;
"db_type"       return TYPE;
"db_name"       return NAME;
"db_table_prefix" return TABLE_PREFIX;
"db_port"       return PORT;

[a-zA-Z][_a-zA-z0-9]*     return IDENTIFIER;
[1-9][0-9]*               return INTEGER;
[ \t\n]                   ;
.                         printf("unexpected character\n");
 
%%

int yywrap(void){
    return 1;
}

// flex lexer.l 
// cc lex.yy.c -ll
// ./a.out

// abc
// [a-zA-Z]
// dog.*cat
// (ab)+         ->  ababab...
// [^a-z]+       ->  matches string of noe or more characters but not include a-z.
// [+-]?[0-9]+   ->  match any string of noe or more digits with an optional prefix of + or -.


