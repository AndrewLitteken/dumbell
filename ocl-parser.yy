%{
#include <string>
#include <vector>
#include <iostream>
#include <utility>

typedef std::pair<int, bool> scope_info;

std::vector<scope_info> scope_stack;
int max_stack_size = 1;
int indent_level = 0;
bool ws_define = false;
bool spaces = false;
bool if_open = false;
int indent_count;

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

program : line_list

line_list   : line line_list
            | indent line line_list
            | /*empty*/
            ;

line: decl
    | stmt
    | TOKEN_NEWLINE
    ;

fill_line   : decl
            | stmt
            ;

decl: name ws TOKEN_ASSIGN ws TOKEN_FUNCTION TOKEN_LEFT_PAREN arg_list TOKEN_RIGHT_PAREN ws TOKEN_COLON TOKEN_NEWLINE indent fill_line
    { }
    | name ws TOKEN_DEFINITION ws expr ws TOKEN_NEWLINE
    | name ws TOKEN_ASSIGN ws expr ws TOKEN_NEWLINE
    ;

stmt: TOKEN_PRINT TOKEN_LEFT_PAREN expr TOKEN_RIGHT_PAREN TOKEN_NEWLINE
    | TOKEN_IF ws expr ws TOKEN_COLON TOKEN_NEWLINE indent fill_line
    { if_open = true; }
    | TOKEN_ELSE TOKEN_SPACE TOKEN_IF ws expr ws TOKEN_COLON TOKEN_NEWLINE indent fill_line
    { if(!if_open) YYERROR; }
    | TOKEN_ELSE ws TOKEN_COLON TOKEN_NEWLINE indent fill_line
    { if(!if_open) YYERROR;
      else if_open = false;
    }
    | TOKEN_WHILE ws expr ws TOKEN_COLON TOKEN_NEWLINE indent line
    | TOKEN_RETURN ws expr TOKEN_NEWLINE
    ;

expr: value_literals
    ;

indent  : TOKEN_TAB indent_tab_opt
        {if(!ws_define) {
            ws_define = true;
            spaces = false;
         }
         if(spaces) YYERROR;
         indent_count = 1;
        }
        | TOKEN_SPACE indent_sp_opt
        {if(!ws_define) {
            ws_define = true;
            spaces = true;
         }
         if(!spaces) YYERROR;
         indent_count = 1;
        }
        ;

indent_tab_opt: TOKEN_TAB indent_tab_opt
              { indent_count++; }
              | /*empty*/
              ;

indent_sp_opt : TOKEN_SPACE indent_sp_opt
              { indent_count++; };
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
