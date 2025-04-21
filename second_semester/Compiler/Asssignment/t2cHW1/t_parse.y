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
prog	:	mthdcls
		{ printf("Program -> MethodDecls\n");
		  printf("Parsed OK!\n"); }
	|
		{ printf("****** Parsing failed!\n"); }	
	;

mthdcls	:	mthdcl mthdcls
		{ printf("MethodDecls -> MethodDecl MethodDecls\n"); }	
	|	mthdcl
		{ printf("MethodDecls -> MethodDecl\n"); }	
	;

type	:	lINT
		{ printf("Type -> INT\n"); }	
	|	lREAL
		{ printf("Type -> REAL\n"); }	
	;

mthdcl	:	type lMAIN lID lLP formals lRP block
		{ printf("MethodDecl -> Type MAIN ID LP Formals RP Block\n"); }	
	|	type lID lLP formals lRP block
		{ printf("MethodDecl -> Type ID LP Formals RP Block\n"); }	
	;

formals	:	formal oformal
		{ printf("Formals -> Formal OtherFormals\n"); }	
	|
		{ printf("Formals -> \n"); }	
	;

formal	:	type lID
		{ printf("Formal -> Type ID\n"); }	
	;

oformal	:	lCOMMA formal oformal
		{ printf("OtherFormals -> COMMA Formal OtherFormals\n"); }	
	|
		{ printf("OtherFormals -> \n"); }	
	;

stmt
	: block
		{ printf("Statement -> Block\n"); }
	| localvardecl
		{ printf("Statement -> LocalVarDecl\n"); }
	| assignstmt
		{ printf("Statement -> AssignStmt\n"); }
	| returnstmt
		{ printf("Statement -> ReturnStmt\n"); }
	| ifstmt
		{ printf("Statement -> IfStmt\n"); }
	| writestmt
		{ printf("Statement -> WriteStmt\n"); }
	| readstmt
		{ printf("Statement -> ReadStmt\n"); }
	;

block
	: lBEGIN stmts lEND
		{ printf("Block -> BEGIN Statement+ END\n"); }
	;

stmts
	: stmt stmts
		{ printf("Statements -> Statement Statements\n"); }
	| stmt
		{ printf("Statements -> Statement\n"); }
	;

localvardecl
	: type lID lSEMI
		{ printf("LocalVarDecl -> Type ID SEMI\n"); }
	| type assignstmt
		{ printf("LocalVarDecl -> Type AssignStmt\n"); }
	;

assignstmt
	: lID lASSIGN expr lSEMI
		{ printf("AssignStmt -> ID := Expression SEMI\n"); }
	;

returnstmt
	: lRETURN expr lSEMI
		{ printf("ReturnStmt -> RETURN Expression SEMI\n"); }
	;

ifstmt
	: lIF lLP boolexpr lRP stmt
		{ printf("IfStmt -> IF ( BoolExpression ) Statement\n"); }
	| lIF lLP boolexpr lRP stmt lELSE stmt
		{ printf("IfStmt -> IF ( BoolExpression ) Statement ELSE Statement\n"); }
	;

writestmt
	: lWRITE lLP expr lCOMMA lQSTR lRP lSEMI
		{ printf("WriteStmt -> WRITE ( Expression , QString ) SEMI\n"); }
	;

readstmt
	: lREAD lLP lID lCOMMA lQSTR lRP lSEMI
		{ printf("ReadStmt -> READ ( ID , QString ) SEMI\n"); }
	;

expr
	: expr lADD term
		{ printf("Expression -> Expression + Term\n"); }
	| expr lMINUS term
		{ printf("Expression -> Expression - Term\n"); }
	| term
		{ printf("Expression -> Term\n"); }
	;

term
	: term lTIMES factor
		{ printf("MultiplicativeExpr -> MultiplicativeExpr * Factor\n"); }
	| term lDIVIDE factor
		{ printf("MultiplicativeExpr -> MultiplicativeExpr / Factor\n"); }
	| factor
		{ printf("MultiplicativeExpr -> Factor\n"); }
	;

factor
	: lINUM
		{ printf("PrimaryExpr -> INUM\n"); }
	| lRNUM
		{ printf("PrimaryExpr -> RNUM\n"); }
	| lID
		{ printf("PrimaryExpr -> ID\n"); }
	| lLP expr lRP
		{ printf("PrimaryExpr -> ( Expression )\n"); }
	| lID lLP actualparams lRP
		{ printf("PrimaryExpr -> ID ( ActualParams )\n"); }
	;

boolexpr
	: expr lEQU expr
		{ printf("BoolExpr -> Expression == Expression\n"); }
	| expr lNEQ expr
		{ printf("BoolExpr -> Expression != Expression\n"); }
	| expr lGT expr
		{ printf("BoolExpr -> Expression > Expression\n"); }
	| expr lGE expr
		{ printf("BoolExpr -> Expression >= Expression\n"); }
	| expr lLT expr
		{ printf("BoolExpr -> Expression < Expression\n"); }
	| expr lLE expr
		{ printf("BoolExpr -> Expression <= Expression\n"); }
	;

actualparams
	: expr lCOMMA actualparams
		{ printf("ActualParams -> Expression , ActualParams\n"); }
	| expr
		{ printf("ActualParams -> Expression\n"); }
	| 
		{ printf("ActualParams -> \n"); }
	;

%%

int yyerror(char *s)
{
	printf("%s\n",s);
	return 1;
}

