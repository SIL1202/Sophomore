#include <main.h>
#include<stdio.h>

extern int yylex();
extern char* yytext;
extern int yylineno;

char* names[] = {NULL, "IDENTIFIER", "INTEGER", "FLOAT"};

int main() {
  int ntoken;
  ntoken = yylex();
  while(ntoken){
    switch(ntoken){
      case IDENTIFIER:
        printf("%s: %s\n", names[ntoken], yytext);
      break;
      case INTEGER:
        printf("%s: %s\n", names[ntoken], yytext);
      break;
      case FLOAT:
        printf("%s: %s\n", names[ntoken], yytext);
      break;
      default:
        printf("unexpected token\n");
      break;
    }
    ntoken = yylex();
  }
  return 0;
}
