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


block   :	lBEGIN stmts lEND
		{ printf("Block -> BEGIN Statements END\n"); }
	;

stmts	:	stmt stmts
		{ printf("Statements -> Statement Statements\n"); }
	|	stmt
		{ printf("Statements -> Statement\n"); }
	;

stmt	:	block
		{ printf("Statement -> Block\n"); }
	|	localdcl
		{ printf("Statement -> LocalVarDecl\n"); }
	|	assignstmt
		{ printf("Statement -> AssignStmt\n"); }
	|	returnstmt
		{ printf("Statement -> ReturnStmt\n"); }
	|	ifstmt
		{ printf("Statement -> IfStmt\n"); }
	|	writestmt
		{ printf("Statement -> WriteStmt\n"); }
	|	readstmt
		{ printf("Statement -> Readstmt\n"); }
	;

localdcl:	type lID lSEMI
		{ printf("LocalVarDecl -> Type Id ;\n"); }
	|	type assignstmt
		{ printf("LocalVarDecl -> Type AssignStmt\n"); }
	;

assignstmt:	lID lASSIGN expr lSEMI
		{ printf("AssignStmt -> Id := Expression ;\n"); }
	;

returnstmt:	lRETURN expr lSEMI
		{ printf("ReturnStmt -> RETURN Expression ;\n"); }
	;

ifstmt	:	lIF lLP boolexpr lRP stmt
		{ printf("IfStmt -> IF ( BoolExpression ) Statement\n"); }
	|	lIF lLP boolexpr lRP stmt lELSE stmt
		{ printf("IfStmt -> IF ( BoolExpression ) Statement ELSE Statement\n"); }
	;

writestmt:	lWRITE lLP expr lCOMMA lQSTR lRP lSEMI
		{ printf("WriteStmt -> WRITE ( Expression , QString ) ;\n"); }
	;

readstmt:	lREAD lLP lID lCOMMA lQSTR lRP lSEMI
		{ printf("ReadStmt -> READ ( Id , QString ) ;\n"); }
	;


expr 	: 	mulexpr exprtail
		{ printf("Expression -> MultiplicativeExpr ExpressionTail\n"); }
	;

exprtail:	
		{ printf("ExpressionTail -> \n"); }
	|	lADD mulexpr exprtail
		{ printf("ExpressionTail -> plus MultiplicativeExpr ExpressionTail\n"); }
	|	lMINUS mulexpr exprtail
		{ printf("ExpressionTail -> minus MultiplicativeExpr ExpressionTail\n"); }
	;	

mulexpr : 	primaryexpr multail
		{ printf("MultiplicativeExpr -> PrimaryExpression MultiTail\n"); }
	;

multail	:	
		{ printf("MultiTail -> \n"); }
	|	lTIMES primaryexpr multail
		{ printf("MultiTail -> times PrimaryExpression MultTail\n"); }
	|	lDIVIDE primaryexpr multail
		{ printf("MultiTail -> divides PrimaryExpression MultTail\n"); }
	;

primaryexpr: 	lINUM
		{ printf("PrimaryExpr -> INUM\n"); }
	| 	lRNUM
		{ printf("PrimaryExpr -> RNUM\n"); }
	| 	lID
		{ printf("PrimaryExpr -> ID\n"); }
	| 	lLP expr lRP
		{ printf("PrimaryExpr -> ( Expression )\n"); }
	| 	lID lLP actuals lRP
		{ printf("PrimaryExpr -> ID ( ActualParams )\n"); }
	;

boolexpr: 	expr lEQU expr
		{ printf("BoolExpr -> Expression == Expression\n"); }
	| 	expr lNEQ expr
		{ printf("BoolExpr -> Expression != Expression\n"); }
	| 	expr lGT expr
		{ printf("BoolExpr -> Expression > Expression\n"); }
	| 	expr lGE expr
		{ printf("BoolExpr -> Expression >= Expression\n"); }
	| 	expr lLT expr
		{ printf("BoolExpr -> Expression < Expression\n"); }
	| 	expr lLE expr
		{ printf("BoolExpr -> Expression <= Expression\n"); }
	;

actuals : 	expr oactuals
		{ printf("ActualParams -> Expression OtherParams\n"); }
	| 
		{ printf("ActualParams -> \n"); }
	;

oactuals: 	lCOMMA expr oactuals
		{ printf("OtherParams -> COMMA Expression OtherParams\n"); }
	| 
		{ printf("OtherParams -> \n"); }
	;

%%

int yyerror(char *s)
{
	printf("%s\n",s);
	return 1;
}

