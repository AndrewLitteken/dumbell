%{
#include <string>
#include <vector>
#include <iostream>
%}

%skeleton "lalr1.cc"

%define "parser_class_name" {Parser}

%defines "ocl-parser.h"

%debug

%locations
%initial-action
{
    @$.begin.filename = @$.end.filename = &driver.streamname;
}

%parse-param { class oclDriver& driver }

%token TOKEN_EOF 0
%token TOKEN_COMMENT
%token TOKEN_IDENTIFIER
%token TOKEN_INTEGER_LITERAL
%token TOKEN_BOOL_LITERAL
%token TOKEN_FP_LITERAL
%token TOKEN_RIGHT_PAREN
%token TOKEN_LEFT_PAREN
%token TOKEN_RIGHT_BRACKET
%token TOKEN_LEFT_BRACKET
%token TOKEN_RIGHT_BRACE
%token TOKEN_LEFT_BRACE
%token TOKEN_INCREMENT
%token TOKEN_DECREMENT
%token TOKEN_INCEQ
%token TOKEN_DECEQ
%token TOKEN_MULTEQ
%token TOKEN_DIVEQ
%token TOKEN_NOT
%token TOKEN_EXPONENT
%token TOKEN_MULTIPLY
%token TOKEN_DIVIDE
%token TOKEN_MOD
%token TOKEN_ADD
%token TOKEN_MINUS
%token TOKEN_LT
%token TOKEN_LE
%token TOKEN_GT
%token TOKEN_GE
%token TOKEN_EQ
%token TOKEN_NE
%token TOKEN_AND
%token TOKEN_OR
%token TOKEN_IN
%token TOKEN_ASSIGN
%token TOKEN_PRINT
%token TOKEN_FUNCTION
%token TOKEN_NEWLINE
%token TOKEN_FOR
%token TOKEN_IF
%token TOKEN_ELSE
%token TOKEN_RETURN
%token TOKEN_WHILE
%token TOKEN_COLON
%token TOKEN_COMMA
%token TOKEN_ERROR
%token TOKEN_SEMI

%{
#include "ocl-driver.h"
#include "ocl-scanner.h"

#undef yylex
#define yylex driver.lexer->lex

%}

%%
result_list: item result_list
           | /*empty*/
           ;

item: COMMENT
	| IDENTIFIER
	| INTEGER_LITERAL
	| BOOL_LITERAL
	| FP_LITERAL
	| RIGHT_PAREN
	| LEFT_PAREN
	| RIGHT_BRACKET
	| LEFT_BRACKET
	| RIGHT_BRACE
	| LEFT_BRACE
	| INCREMENT
	| DECREMENT
	| INCEQ
	| DECEQ
	| MULTEQ
	| DIVEQ
	| NOT
	| EXPONENT
	| MULTIPLY
	| DIVIDE
	| MOD
	| ADD
	| MINUS
	| LT
	| LE
	| GT
	| GE
	| EQ
	| NE
	| AND
	| OR
	| IN
	| ASSIGN
	| PRINT
	| FUNCTION
	| NEWLINE
	| FOR
	| IF
	| ELSE
	| RETURN
	| WHILE
	| COLON
	| COMMA
	| ERROR
	| SEMI
    ;

COMMENT: TOKEN_COMMENT {std::cout<<"comment"<<std::endl;};
IDENTIFIER: TOKEN_IDENTIFIER {std::cout<<"identifier"<<std::endl;};
INTEGER_LITERAL: TOKEN_INTEGER_LITERAL {std::cout<<"integer"<<std::endl;};
BOOL_LITERAL: TOKEN_BOOL_LITERAL {std::cout<<"boolean"<<std::endl;};
FP_LITERAL: TOKEN_FP_LITERAL {std::cout<<"floating point"<<std::endl;};
RIGHT_PAREN: TOKEN_RIGHT_PAREN {std::cout<<"right paren"<<std::endl;};
LEFT_PAREN: TOKEN_LEFT_PAREN {std::cout<<"left paren"<<std::endl;};
RIGHT_BRACKET: TOKEN_RIGHT_BRACKET {std::cout<<"right bracket"<<std::endl;};
LEFT_BRACKET: TOKEN_LEFT_BRACKET {std::cout<<"left bracket"<<std::endl;};
RIGHT_BRACE: TOKEN_RIGHT_BRACE {std::cout<<"right brace"<<std::endl;};
LEFT_BRACE: TOKEN_LEFT_BRACE {std::cout<<"left brace"<<std::endl;};
INCREMENT: TOKEN_INCREMENT {std::cout<<"increment"<<std::endl;};
DECREMENT: TOKEN_DECREMENT {std::cout<<"decrement"<<std::endl;};
INCEQ: TOKEN_INCEQ {std::cout<<"increment and assign"<<std::endl;};
DECEQ: TOKEN_DECEQ {std::cout<<"decrement and assign"<<std::endl;};
MULTEQ: TOKEN_MULTEQ {std::cout<<"multiply and assign"<<std::endl;};
DIVEQ: TOKEN_DIVEQ {std::cout<<"divide and assign"<<std::endl;};
NOT: TOKEN_NOT {std::cout<<"unary negation"<<std::endl;};
EXPONENT: TOKEN_EXPONENT {std::cout<<"exponential"<<std::endl;};
MULTIPLY: TOKEN_MULTIPLY {std::cout<<"multiply"<<std::endl;};
DIVIDE: TOKEN_DIVIDE {std::cout<<"division"<<std::endl;};
MOD: TOKEN_MOD {std::cout<<"modulus"<<std::endl;};
ADD: TOKEN_ADD {std::cout<<"addtion"<<std::endl;};
MINUS: TOKEN_MINUS {std::cout<<"subtraction"<<std::endl;};
LT: TOKEN_LT {std::cout<<"less than"<<std::endl;};
LE: TOKEN_LE {std::cout<<"less than or equal"<<std::endl;};
GT: TOKEN_GT {std::cout<<"greater than"<<std::endl;};
GE: TOKEN_GE {std::cout<<"greater than or equal"<<std::endl;};
EQ: TOKEN_EQ {std::cout<<"equality"<<std::endl;};
NE: TOKEN_NE {std::cout<<"not equal"<<std::endl;};
AND: TOKEN_AND {std::cout<<"boolean and"<<std::endl;};
OR: TOKEN_OR {std::cout<<"boolean or"<<std::endl;};
IN: TOKEN_IN {std::cout<<"in"<<std::endl;};
ASSIGN: TOKEN_ASSIGN {std::cout<<"assignment"<<std::endl;};
PRINT: TOKEN_PRINT {std::cout<<"print"<<std::endl;};
FUNCTION: TOKEN_FUNCTION {std::cout<<"function definition"<<std::endl;};
NEWLINE: TOKEN_NEWLINE {std::cout<<"new line"<<std::endl;};
FOR: TOKEN_FOR {std::cout<<"for"<<std::endl;};
IF: TOKEN_IF {std::cout<<"if"<<std::endl;};
ELSE: TOKEN_ELSE {std::cout<<"else"<<std::endl;};
RETURN: TOKEN_RETURN {std::cout<<"return"<<std::endl;};
WHILE: TOKEN_WHILE {std::cout<<"while"<<std::endl;};
COLON: TOKEN_COLON {std::cout<<"colon"<<std::endl;};
COMMA: TOKEN_COMMA {std::cout<<"comma"<<std::endl;};
SEMI: TOKEN_SEMI {std::cout<<"semi"<<std::endl;}; 
ERROR: TOKEN_ERROR {std::cout<<"error"<<std::endl;};
%%

void yy::Parser::error(const yy::location& l, const std::string& m){
    driver.error(l, m);
}
