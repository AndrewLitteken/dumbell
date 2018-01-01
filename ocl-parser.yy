%{
#include <string>
#include <vector>
#include <iostream>
#include <utility>

typedef std::pair<int, bool> scope_info;

extern std::vector<scope_info> scope_stack;

int max_stack_size = 1;
int indent_level = 0;
bool ws_define = false;
bool spaces = false;
bool if_open = false;
int indent_count;

bool check_indents(std::string);
%}

%skeleton "lalr1.cc"

%union{
    std::string* str;
    int num;
}

%define "parser_class_name" {Parser}

%defines "ocl-parser.h"

%debug

%locations
%initial-action
{
    @$.begin.filename = @$.end.filename = &driver.streamname;
}

%parse-param { class oclDriver& driver }

%error-verbose

%token TOKEN_EOF 0
%token <str> TOKEN_INDENT_TAB
%token <str> TOKEN_INDENT_SPACE
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
%token TOKEN_DEFINITION
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

extern int line_num;

#undef yylex
#define yylex driver.lexer->lex

%}

%%

program : line_list

line_list   : line line_list
            | indent line line_list
            | /*empty*/
            ;

line: decl TOKEN_NEWLINE
    | stmt TOKEN_NEWLINE
    | TOKEN_NEWLINE
    ;

fill_line   : decl
            | stmt
            ;

decl: name TOKEN_ASSIGN TOKEN_FUNCTION TOKEN_LEFT_PAREN arg_list TOKEN_RIGHT_PAREN TOKEN_COLON suite
    | name TOKEN_DEFINITION expr 
    | name TOKEN_ASSIGN expr 
    ;

stmt: TOKEN_PRINT TOKEN_LEFT_PAREN expr TOKEN_RIGHT_PAREN
    { if(if_open) if_open = false; }
    | TOKEN_IF expr TOKEN_COLON suite
    { if_open = true; }
    | TOKEN_ELSE TOKEN_IF expr TOKEN_COLON suite
    { }
    | TOKEN_ELSE TOKEN_COLON suite
    { 
    }
    | TOKEN_WHILE expr TOKEN_COLON suite
    { if(if_open) if_open = false; }
    | TOKEN_RETURN expr
    { if(if_open) if_open = false; }
    ;

suite: TOKEN_NEWLINE indent fill_line

expr	: expr TOKEN_ASSIGN expr_or
		| expr TOKEN_INCEQ expr_or
		| expr TOKEN_DECEQ expr_or
		| expr TOKEN_MULTEQ expr_or
		| expr TOKEN_DIVEQ expr_or
        | expr_or
		;

expr_or	: expr_or TOKEN_OR expr_and
		| expr_and
		;
		
expr_and: expr_and TOKEN_AND expr_eq
		| expr_eq
		;

expr_eq	: expr_eq TOKEN_EQ expr_comp
        | expr_eq TOKEN_NE expr_comp
		| expr_comp
		;

expr_comp	: expr_comp TOKEN_LT expr_add
		| expr_comp TOKEN_LE expr_add
		| expr_comp TOKEN_GT expr_add
		| expr_comp TOKEN_GE expr_add
		| expr_add

expr_add: expr_add TOKEN_ADD expr_mul
		| expr_add TOKEN_MINUS expr_mul
		| expr_mul
		;

expr_mul: expr_mul TOKEN_MULTIPLY expr_exp
	 	| expr_mul TOKEN_DIVIDE expr_exp
		| expr_mul TOKEN_MOD expr_exp
		| expr_exp
		;

expr_exp: expr_exp TOKEN_EXPONENT expr_bool
		| expr_bool
		;

expr_bool: TOKEN_NOT non_int_literal
		| TOKEN_NOT name
		| non_int_literal
		| expr_minus
		;

expr_minus	: TOKEN_MINUS expr_int
		| expr_int
		;

expr_int: value_literals
		| expr_inc
		;		

expr_inc: expr_inc TOKEN_INCREMENT
        | expr_inc TOKEN_DECREMENT
		| expr_grp
		;

expr_grp: TOKEN_LEFT_PAREN expr TOKEN_RIGHT_PAREN
		| name
		//| name TOKEN_LEFT_PAREN expr_list TOKEN_RIGHT_PAREN
        ;

indent  : TOKEN_INDENT_TAB
        { check_indents(*$1);}
        | TOKEN_INDENT_SPACE
        { check_indents(*$1);}
        ;

arg_list: arg TOKEN_COMMA arg_list
        | arg
        | /*empty*/
        ;

arg : name
    | name TOKEN_ASSIGN expr
    ;

value_literals  : TOKEN_INTEGER_LITERAL
                | TOKEN_FP_LITERAL
                ;

non_int_literal : TOKEN_BOOL_LITERAL
                ;

name: TOKEN_IDENTIFIER
    ;
%%

bool check_indents(std::string text){
    int found = -1;
    if(text.length() < scope_stack.back().first){
        for(int i = 0;i<scope_stack.size();i++){
            if(scope_stack[i].first == text.length()){
                found = i;
                break;
            }
        }
        if(found < 0) {
            std::cout<<line_num<<": Indentation level not defined\n";
            exit(1);
        }
        for(int i = scope_stack.size()-1;i>found;i--) scope_stack.pop_back();
    }
    else if(text.length() > scope_stack.back().first){
        scope_info new_line = std::make_pair(text.length(), false);
        scope_stack.push_back(new_line);
        found = scope_stack.size()-1;
    }
    else found = scope_stack.size() - 1;
    return found;
}

void yy::Parser::error(const yy::location& l, const std::string& m){
    std::cout<<line_num<<" "<<m<<std::endl;
    driver.error(l, m);
}
