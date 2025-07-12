







<!-- COVER PAGE -->

<div style="page-break-after: always; text-align: center; margin-top: 200px;">


# Programming Assignment #1  


**Department of Computer Science and Information Engineering**  

grade: sphomore

group: 胡師睿、劉家均

student ID: 411221301、411221426

professor: Chung Yung

</div>

------

## I. Problem Description

The objective of this assignment is to implement the front end of a compiler for the T programming language using **Flex** (Lex) and **Bison** (Yacc). This includes building a **lexical analyzer** and a **syntax recognizer**, capable of parsing T programs and showing the grammar rules applied during parsing.

The T language specification includes:

- **Lexical elements**: keywords (e.g., `WRITE`, `READ`, `IF`), operators, separators, identifiers, integers, real numbers, comments, and quoted strings.
- **Grammar rules**: specified in EBNF for expressions, statements, blocks, method declarations, etc.

The compiler must recognize valid T programs and provide traceable output of applied grammar rules.

------

## II. Highlights of Implementation

The implementation is modularized into distinct files:

- `t_lex.l`: defines the lexical rules using Flex for tokenizing input.
- `t_parse.y`: specifies the grammar and parsing rules using Bison.
- `t2c.c`: contains the main function used to launch the parser.
- `t2c.h`: header file shared between components.

### Lexical Analyzer (`t_lex.l`)

- Implements all token definitions including keywords (`WRITE`, `READ`, etc.), identifiers, integers, real numbers, and string literals.
- Special handling for multi-line comments and escaped strings.
- Tokens such as `:=`, `>=`, `<=`, `==`, etc., are correctly recognized using longest-match rules.
- Uses global variables (`ival`, `rval`, `name`, `qstr`) to carry semantic values to the parser.

### Syntax Recognizer (`t_parse.y`)

- Follows the T language grammar closely, implementing rules for `Program`, `MethodDecl`, `Block`, `Statement`, `Expression`, and `BoolExpr`.

- Each rule is instrumented with `printf()` to display the production used, which helps in visualizing the parsing process.

- Includes operator precedence and associativity for correct parsing of expressions.

- Handles nested blocks, multiple parameters, and function calls as expressions.

  


### Main Driver (`t2c.c`)

- Initializes parsing with `yyparse()` and optionally prints the result of the compilation process.
- Designed for future extension into intermediate code generation or semantic checking.

### Build System (`Makefile`)

- Automates the steps of converting `.l` and `.y` files to `.c`, then compiling and linking them into an executable named `parse`.
- Allows developers to rebuild the project with a single `make` command.

### Additional Tools

- `t_lexMain.c` provided for debugging or testing just the lexical scanner.
- Modular structure and strict file separation make the code maintainable and scalable.

------

## III. Program Listing

The following files make up the implementation:

- #### `t_lex.l`: Defines tokens including identifiers, keywords, operators, numbers, strings, and comments.
```c
{ID}   { strcpy(name, yytext); return lID; }
{DIG}  { ival = atoi(yytext); return lINUM; }
{RNUM} { rval = atof(yytext); return lRNUM; }
```

#### **Explanation:**

- The first rule matches identifiers (variable names). `yytext` contains the matched string, which is copied into the global variable `name` so it can be used later in parsing. It then returns the `lID` token.
- The second rule matches digit sequences (integers). It converts the text into an integer using `atoi()` and stores the value in `ival`, then returns `lINUM`.
- The third rule matches real numbers with a decimal point. The matched string is converted to a floating-point number using `atof()` and stored in `rval`, then the token `lRNUM` is returned.

This setup allows the parser to use the exact value of identifiers and literals during grammar reductions or future semantic analysis.

- ### `t_parse.y`: Implements grammar rules for T, such as `Program`, `Expression`, `Statement`, `BoolExpression`, etc. Includes precedence and associativity rules.

  ```c
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
  
  expr : mexpr exprtail { printf("Expr -> MExpr ExprTail\n"); }
       ;
  
  exprtail : lADD mexpr exprtail { 
               printf("ExprTail -> + MExpr ExprTail\n");
             }
           | lMINUS mexpr exprtail { 
               printf("ExprTail -> - MExpr ExprTail\n");
             }
           | { printf("ExprTail -> ε\n"); } 
           ;
  
  mexpr : factor mexprtail { printf("MExpr -> Factor MExprTail\n"); }
        ;
  
  mexprtail : lTIMES factor mexprtail { 
                printf("MExprTail -> * Factor MExprTail\n");
              }
            | lDIVIDE factor mexprtail { 
                printf("MExprTail -> / Factor MExprTail\n");
              }
            | { printf("MExprTail -> ε\n"); }
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
  ```

  #### **Explanation of Major Grammar Rules:**

  - `stmt`: A single statement can be a block, declaration, assignment, return, if-statement, write, or read. Each sub-rule prints its structure for debugging.
  - `block`: Represents a sequence of statements enclosed by `BEGIN ... END`.
  - `stmts`: Allows recursive definition of multiple statements.
  - `localvardecl`: Covers both simple declarations (e.g., `INT x;`) and initialized declarations (`INT x := 3;`).
  - `assignstmt`: Assigns an expression to an identifier (e.g., `x := 5;`).
  - `returnstmt`: A return statement like `RETURN x + y;`.
  - `ifstmt`: Handles both `IF (...) stmt` and `IF (...) stmt ELSE stmt` forms.
  - `writestmt` & `readstmt`: Model I/O syntax using expressions and quoted strings.
  - `expr`, `exprtail`, `mexpr`, `mexprtail`: Represent standard expression parsing using recursive descent for left-to-right associativity.
  - `factor`: Covers literals, variables, grouped expressions, and function calls.
  - `boolexpr`: Logical comparisons like `x == y`, `a >= b`, etc.
  - `actualparams`: Parses the parameters passed into function calls, including optional empty argument lists.

  These rules allow the parser to handle real T programs such as function definitions, variable usage, I/O, and control flow.

  

- ### `t2c.c`: Main function invoking `yyparse()`.
- ### `t2c.h`: Provides shared declarations.

Other supporting files:

- `Makefile`: Automates the compilation process.
- `t_lexMain.c`: An alternative or debugging entry point.
- `README.md`: Provides basic instructions.

------

## IV. Test Run Results

Multiple `.t` test files were prepared and executed:

- **test.t**: Full sample program with function calls and I/O.
- **test1.t** to **test7.t**: Various edge cases including empty parameters, different arithmetic combinations, nested blocks, if-else branches, and return expressions.

Each test case successfully triggered the appropriate grammar rule reductions and reported lexical tokens as expected. The program correctly identifies invalid syntax when introduced.

------

## V. Discussion

This assignment demonstrates a practical understanding of how compilers tokenize and parse high-level languages. Key insights include:

- The significance of precise token definitions for correct parsing.
- How operator precedence and associativity are handled in Bison.
- The value of separating lexical and syntax concerns for modularity.

Challenges included managing nested rules and ensuring that the parser properly handled all expression forms, particularly function calls as part of expressions.

Future improvements could include:

- Adding a semantic analysis phase.
- Generating intermediate code (e.g., 3-address code).
- Enhanced error reporting and recovery.

------

End of Report.
