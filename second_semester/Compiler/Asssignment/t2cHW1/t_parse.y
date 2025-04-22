%{ 
    #include <stdio.h>
    #include <stdlib.h>
    #include "t2c.h"
    #include "t_parse.h"
%}

%token lWRITE lREAD lIF lASSIGN
%token lRETURN lBEGIN lEND
%left  lEQU lNEQ lGT lLT lGE lLE
%left  lADD lMINUS
%left  lTIMES lDIVIDE
%token lLP lRP
%token lINT lREAL lSTRING
%token lELSE
%token lMAIN
%token lSEMI lCOMMA
%token lID lINUM lRNUM lQSTR

%expect 1

%%
prog    : mthdcls
        { printf("Program -> MethodDecls\n");
          printf("Parsed OK!\n"); }
    ;

mthdcls : mthdcl mthdcls { printf("MethodDecls -> MethodDecl MethodDecls\n"); }
        | mthdcl         { printf("MethodDecls -> MethodDecl\n"); }
    ;

type    : lINT           { printf("Type -> INT\n"); }
        | lREAL         { printf("Type -> REAL\n"); }
    ;

mthdcl  : type lMAIN lID lLP formals lRP block
        { printf("MethodDecl -> Type MAIN ID LP Formals RP Block\n");
          printf("Main method parsed\n"); }
        | type lID lLP formals lRP block
        { printf("MethodDecl -> Type ID LP Formals RP Block\n");
          printf("Function parsed\n"); }
    ;

formals : formal oformal { printf("Formals -> Formal OtherFormals\n"); }
        |                { printf("Formals -> \n"); }
    ;

formal  : type lID       { printf("Formal -> Type ID\n"); }
    ;

oformal : lCOMMA formal oformal { printf("OtherFormals -> COMMA Formal OtherFormals\n"); }
        |                      { printf("OtherFormals -> \n"); }
    ;

Statements
    : Statement         { printf("Statements -> Statement\n"); }
    | Statement Statements { printf("Statements -> Statement Statements\n"); }
    ;

Statement
    : AssignStmt       { printf("Statement -> AssignStmt\n"); }
    | ReturnStmt       { printf("Statement -> ReturnStmt\n"); }
    | ReadStmt         { printf("Statement -> ReadStmt\n"); }
    | WriteStmt        { printf("Statement -> WriteStmt\n"); }
    | LocalVarDecl     { printf("Statement -> LocalVarDecl\n"); }
    | IfStmt          { printf("Statement -> IfStmt\n"); }
    | block           { printf("Statement -> Block\n"); }
    ;

block
    : lBEGIN Statements lEND
        { printf("Block -> BEGIN Statements END\n");
          printf("Block parsed\n"); }
    ;

LocalVarDecl
    : type lID lSEMI   
        { printf("LocalVarDecl -> Type ID SEMI\n");
          printf("Variable name: ID\n");  // 新增
          printf("Declaration complete\n"); }  // 新增
    ;

AssignStmt
    : lID lASSIGN expr lSEMI
        { printf("AssignStmt -> ID := Expression SEMI\n");
          printf("Assignment expression parsed\n");  // 新增
          printf("End of assignment\n"); }  // 新增
    ;

ReturnStmt
    : lRETURN expr lSEMI
        { printf("ReturnStmt -> RETURN Expression SEMI\n");
          printf("Return value expression parsed\n");  // 新增
           }  // 新增
    ;

IfStmt
    : lIF lLP boolexpr lRP Statement
        { printf("IfStmt -> IF ( BoolExpression ) Statement\n");
          printf("If parsed\n"); }
    | lIF lLP boolexpr lRP Statement lELSE Statement
        { printf("IfStmt -> IF ( BoolExpression ) Statement ELSE Statement\n");
          printf("If-else parsed\n"); }
    ;

WriteStmt
    : lWRITE lLP expr lCOMMA lQSTR lRP lSEMI
        { printf("WriteStmt -> WRITE ( Expression , QString ) SEMI\n");
          printf("Write parsed\n"); }
    ;

ReadStmt
    : lREAD lLP lID lCOMMA lQSTR lRP lSEMI
        { printf("ReadStmt -> READ ( ID , QString ) SEMI\n");
          printf("Read parsed\n"); }
    ;

expr
    : expr lADD term { 
          printf("Expression -> Expression + Term\n");
          printf("Addition operation\n");  // 新增 
      }
    | expr lMINUS term { printf("Expression -> Expression - Term\n"); }
    | term            { printf("Expression -> Term\n"); }
    ;

term
    : term lTIMES factor { printf("Term -> Term * Factor\n"); }
    | term lDIVIDE factor { printf("Term -> Term / Factor\n"); }
    | factor           { printf("Term -> Factor\n"); }
    ;

factor
    : lINUM           { printf("Factor -> INUM\n"); }
    | lRNUM           { printf("Factor -> RNUM\n"); }
    | lID             { printf("Factor -> ID\n"); }
    | lLP expr lRP    { printf("Factor -> ( Expression )\n"); }
    | lID lLP actualparams lRP { 
    printf("Factor -> ID ( ActualParams )\n");
    }    ;

boolexpr
    : expr lEQU expr  { printf("BoolExpr -> Expression == Expression\n"); }
    | expr lNEQ expr  { printf("BoolExpr -> Expression != Expression\n"); }
    | expr lGT expr   { printf("BoolExpr -> Expression > Expression\n"); }
    | expr lGE expr   { printf("BoolExpr -> Expression >= Expression\n"); }
    | expr lLT expr   { printf("BoolExpr -> Expression < Expression\n"); }
    | expr lLE expr   { printf("BoolExpr -> Expression <= Expression\n"); }
    ;

actualparams
    : expr lCOMMA actualparams { printf("ActualParams -> Expression , ActualParams\n"); }
    | expr            { printf("ActualParams -> Expression\n"); }
    |                 { printf("ActualParams -> \n"); }
    ;

%%

int yyerror(char *s)
{ 
    printf("%s\n",s);
    return 1;
}

