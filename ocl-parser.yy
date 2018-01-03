%{
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "line.h"

typedef std::pair<int, std::vector<bool> > scope_info;

extern std::vector<scope_info> scope_stack;
Line *syntax_tree;
std::vector<Line *> tails;

int max_stack_size = 1;
std::vector<int> indent_levels;
bool ws_define = false;
bool spaces = false;
int indent_level_count = -1;

bool loop_available();
int check_indents(std::string);
void indent_levels_add(int);
bool check_indent_levels();
%}

%skeleton "lalr1.cc"

%union{
    std::string* str;
    int num;
    class Line *line;
    class Expr *expr;
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
%token TOKEN_BREAK
%token TOKEN_PASS
%token TOKEN_CONTINUE
%token TOKEN_COLON
%token TOKEN_COMMA
%token TOKEN_ERROR
%token TOKEN_SEMI

%type <num> indent begin_indent
%type <line> program line_list line
%{
#include "ocl-driver.h"
#include "ocl-scanner.h"

extern int line_num;

#undef yylex
#define yylex driver.lexer->lex

%}

%%

program : line_list
        { $$ = syntax_tree; }

line_list   : line line_list
            | /*empty*/
            ;

line: begin_indent line_type TOKEN_NEWLINE
    { 
        indent_levels.clear(); 
        indent_level_count = -1;
    }
    | TOKEN_NEWLINE
    ;

line_type   : decl
            | stmt
            ;

fill_line   : decl
            | stmt
            | TOKEN_PASS
            | TOKEN_NEWLINE fill_line
            | TOKEN_NEWLINE indent fill_line
            ;

decl: name TOKEN_ASSIGN TOKEN_FUNCTION TOKEN_LEFT_PAREN arg_list TOKEN_RIGHT_PAREN TOKEN_COLON TOKEN_NEWLINE indent fill_line
    | name TOKEN_DEFINITION expr 
    | name TOKEN_ASSIGN expr 
    ;

stmt: TOKEN_PRINT TOKEN_LEFT_PAREN expr TOKEN_RIGHT_PAREN
    { if(scope_stack.back().second[0]) scope_stack.back().second[0] = false; }
    | TOKEN_IF expr TOKEN_COLON TOKEN_NEWLINE indent fill_line
    { 
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for an if statement\n";
            exit(1);
        }
        scope_stack[$5-1].second[0] = true;
    }
    | TOKEN_ELSE TOKEN_IF expr TOKEN_COLON TOKEN_NEWLINE indent fill_line
    { 
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for an else if statement\n";
            exit(1);
        }
        if(!scope_stack[$6-1].second[0]){
            std::cout<<"Line "<<line_num-2<<": No If-statement defined at current scope\n";
            exit(1);
        }
    }
    | TOKEN_ELSE TOKEN_COLON TOKEN_NEWLINE indent fill_line
    {    
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for an else statement\n";
            exit(1);
        }
        if(!scope_stack[$4-1].second[0]){
            std::cout<<"Line "<<line_num-2<<": No If-statement defined at current scope\n";
            exit(1);
        }
        else{
            scope_stack[$4-1].second[0] = false; 
        } 
    }
    | TOKEN_WHILE expr TOKEN_COLON TOKEN_NEWLINE indent fill_line
    {  
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for a while loop\n";
            exit(1);
        }
        if(scope_stack[$5-1].second[0]) scope_stack[$5-1].second[0] = false;
        scope_stack[$5].second[1] = true;
    }
    | TOKEN_RETURN expr
    { if(scope_stack.back().second[0]) scope_stack.back().second[0] = false; }
    | loop_control
    { 
      if(scope_stack.back().second[0]) scope_stack.back().second[0] = false; 
      if(!loop_available()){
            std::cout<<"Line "<<line_num<<": Loop not defined\n";
            exit(1);
      }
    }
    ;

loop_control: TOKEN_CONTINUE
            | TOKEN_BREAK
            ;

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
        { 
          max_stack_size++;
          int indent_level = check_indents(*$1) - 1;
          indent_levels_add(indent_level+1);
          $$ = indent_level+1;
        }
        | TOKEN_INDENT_SPACE
        { 
          max_stack_size++;
          int indent_level = check_indents(*$1) - 1;
          indent_levels_add(indent_level+1);
          $$ = indent_level+1;
        }
        ;

begin_indent: TOKEN_INDENT_TAB
            {   if(!ws_define){
                    spaces = false; 
                    ws_define = true;
                }
                if(spaces){
                    std::cout<<line_num<<": Mismatched tabs and spaces\n";
                }
                int indent_level = check_indents(*$1);
                indent_levels_add(indent_level);
                $$ = indent_level;
            }
            | TOKEN_INDENT_SPACE
            {   if(!ws_define){
                    spaces = true; 
                    ws_define = true;
                }
                if(!spaces){
                    std::cout<<line_num<<": Mismatched tabs and spaces\n";
                }
                int indent_level = check_indents(*$1);
                indent_levels_add(indent_level);
                $$ = indent_level;
            }
            | /*empty*/
            {
                for(int i = scope_stack.size()-1;i>0;i--){
                    scope_stack.pop_back();
                }
                indent_levels_add(0);
                max_stack_size = 1;
                $$ = 0;
            }
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

bool loop_available(){
    for(int i = scope_stack.size()-1;i>=0;i--){
        if(scope_stack[i].second[1]) return true;
    }
    return false;
}

int check_indents(std::string text){
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
        max_stack_size = found+1;
        for(int i = scope_stack.size()-1;i>found;i--){
            scope_stack.pop_back();
        }
    }
    else if(text.length() > scope_stack.back().first){
        if(scope_stack.size() > max_stack_size){
            std::cout<<"Line "<<line_num<<": Indent level not defined\n";
            exit(1);
        }
        std::vector<bool> flags;
        flags.push_back(false);
        flags.push_back(false);
        scope_info new_line = std::make_pair(text.length(), flags);
        scope_stack.push_back(new_line);
        found = scope_stack.size()-1;
    }
    else found = scope_stack.size() - 1;
    return found;
}

void indent_levels_add(int to_add){
    indent_levels.push_back(to_add);
}

bool check_indent_levels(){
    if(indent_level_count < 0) indent_level_count = indent_levels.size()-1;
    indent_level_count--;
    return indent_levels[indent_level_count] < indent_levels[indent_level_count+1];
}

void yy::Parser::error(const yy::location& l, const std::string& m){
    std::cout<<line_num<<" "<<m<<std::endl;
    driver.error(l, m);
}
