#include <main.h>
#include <stdio.h>

extern int yylex();
extern char *yytext;
extern int yylineno;

void INT(void) {
  int vartoken = yylex();
  if (vartoken != VARIABLE) {
    printf("expected variable statement\n");
    return;
  }
  int token = yylex();
  if (token == SEMICOLON) {
    return;
  } // else
  token = yylex();
  if (token != EQUAL) {
    printf("Expected ';' at end of declaration\n");
    return;
  }
  int vtoken = yylex();
  if (vtoken != VALUE) {
    printf("Expected expression");
    return;
  }
}

int main() {
  int tytoken, vartoken, vtoken, ntoken;
  tytoken = yylex();
  while (tytoken) {
    switch (tytoken) {
    case INTTYPE:
      INT();
      break;
    case FLOATTYPE:
    case CHARTYPE:
    default:
      break;
    }
    tytoken = yylex();
  }
  return 0;
}
