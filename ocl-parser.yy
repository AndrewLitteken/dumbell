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

%error-verbose

%token TOKEN_EOF 0
%token TOKEN_TAB
%token TOKEN_SPACE
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

program : decl_list

decl_list   : decl decl_list
            | TOKEN_NEWLINE decl_list
            | /*empty*/
            ;

decl: name ws TOKEN_ASSIGN ws TOKEN_FUNCTION TOKEN_LEFT_PAREN arg_list TOKEN_RIGHT_PAREN ws TOKEN_COLON TOKEN_NEWLINE indent low_stmt
    | low_stmt
    ;

low_stmt: name ws TOKEN_DEFINITION ws expr ws TOKEN_NEWLINE
        | name ws TOKEN_ASSIGN ws expr ws TOKEN_NEWLINE
        | name TOKEN_LEFT_PAREN expr TOKEN_RIGHT_PAREN TOKEN_NEWLINE
        | TOKEN_PRINT TOKEN_LEFT_PAREN expr TOKEN_RIGHT_PAREN TOKEN_NEWLINE
        | TOKEN_IF ws expr ws TOKEN_COLON TOKEN_NEWLINE indent low_stmt
        | TOKEN_WHILE ws expr ws TOKEN_COLON TOKEN_NEWLINE indent low_stmt
        ;

expr: value_literals
    ;

indent  : TOKEN_TAB indent_tab_opt
        | TOKEN_SPACE indent_sp_opt
        ;

indent_tab_opt: TOKEN_TAB indent_tab_opt
              | /*empty*/
              ;

indent_sp_opt : TOKEN_SPACE indent_sp_opt
              | /*empty*/
              ;

arg_list: arg TOKEN_COMMA arg_list
        | arg
        | /*empty*/
        ;

arg : name
    | name TOKEN_ASSIGN expr
    ;

ws  : TOKEN_TAB ws
    | TOKEN_SPACE ws
    | /*empty*/
    ;

value_literals  : TOKEN_INTEGER_LITERAL
                | TOKEN_FP_LITERAL
                ;

name: TOKEN_IDENTIFIER
    ;
%%

void yy::Parser::error(const yy::location& l, const std::string& m){
    std::cout<<line_num<<" "<<m<<std::endl;
    driver.error(l, m);
}
