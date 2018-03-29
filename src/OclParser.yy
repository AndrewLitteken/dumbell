%{
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "Line.h"
#include "Expr.h"

typedef std::pair<int, std::vector<bool> > scope_info;

extern std::vector<scope_info> scope_stack;
extern std::vector<Line *> tails;

int max_stack_size = 1;
std::vector<int> indent_levels;
bool ws_define = false;
bool spaces = false;
int indent_level_count = -1;

bool loop_available();
int check_indents(std::string);
void indent_levels_add(int);
bool check_indent_levels();
void add_to_syntax_tree(Line*, int);
%}

%skeleton "lalr1.cc"

%union{
    std::string* str;
    int num;
    class Line *line;
    class Expr *expr;
}

%define "parser_class_name" {Parser}

%defines "OclParser.h"

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
%token <str> TOKEN_IDENTIFIER
%token <str> TOKEN_INTEGER_LITERAL
%token <str> TOKEN_BOOL_LITERAL
%token <str> TOKEN_FP_LITERAL
%token <str> TOKEN_STRING_LITERAL
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
%type <line> program line_list line fill_line stmt decl loop_control line_type
%type <expr> expr expr_or expr_and expr_eq expr_comp expr_add expr_mul expr_exp expr_bool expr_minus expr_int expr_inc expr_grp value_literals non_int_literal arg_list expr_list
%type <str> name
%{
#include "OclDriver.h"
#include "OclScanner.h"

extern int line_num;

#undef yylex
#define yylex driver.lexer->lex

%}

%%

program : line_list
        { driver.syntax_tree = $1; }

line_list   : line line_list
            {
                $$ = $1;
            }
            | /*empty*/
            { }
            ;

line: begin_indent line_type TOKEN_NEWLINE
    { 
        indent_levels.clear(); 
        indent_level_count = -1;
        $$ = $2;
    }
    | TOKEN_NEWLINE
    { }
    ;

line_type   : decl
            {
                $$ = $1;
            }
            | stmt
            {
                $$ = $1;
            }
            ;

fill_line   : decl
            {
                $$ = $1;
            }
            | stmt
            {
                $$ = $1;
            }
            | TOKEN_PASS
            {
                Line *line_to_add = new Line(LINE_PASS, std::string(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, line_num);
                add_to_syntax_tree(line_to_add, -1);    
                $$ = line_to_add;
            }
            | TOKEN_NEWLINE indent fill_line
            {
                $$ = $3;
            }
            ;

decl: name TOKEN_ASSIGN TOKEN_FUNCTION TOKEN_LEFT_PAREN arg_list TOKEN_RIGHT_PAREN TOKEN_COLON TOKEN_NEWLINE indent fill_line
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for a function definition\n";
            exit(1);
        }
        Line *line_to_add = new Line(LINE_FUNC_DEF, *$1, nullptr, nullptr, $5, nullptr, $10, nullptr, line_num);
        add_to_syntax_tree(line_to_add, $9-1);
        $$ = line_to_add;
    }
    | name TOKEN_DEFINITION expr 
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        Line *line_to_add = new Line(LINE_VAR_DEF, *$1, nullptr, nullptr, $3, nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);    
        $$ = line_to_add;
    }
    | expr 
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        Line *line_to_add = new Line(LINE_EXPR, std::string(), nullptr, nullptr, $1, nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);
        $$ = line_to_add;
    }
    ;

stmt: TOKEN_PRINT TOKEN_LEFT_PAREN expr TOKEN_RIGHT_PAREN
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false; 
        Line *line_to_add = new Line(LINE_PRINT, std::string(), nullptr, nullptr, $3, nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);    
        $$ = line_to_add;
    }
    | TOKEN_IF expr TOKEN_COLON TOKEN_NEWLINE indent fill_line
    { 
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for an if statement\n";
            exit(1);
        }
        scope_stack[$5-1].second[0] = true;
        Line *line_to_add = new Line(LINE_IF, std::string(), nullptr, nullptr, $2, nullptr, $6, nullptr, line_num);
        add_to_syntax_tree(line_to_add, $5-1);
        $$ = line_to_add;
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
        Line *line_to_add = new Line(LINE_ELSE_IF, std::string(), nullptr, nullptr, $3, nullptr, $7, nullptr, line_num);
        add_to_syntax_tree(line_to_add, $6-1);
        $$ = line_to_add;
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
        Line *line_to_add = new Line(LINE_ELSE, std::string(), nullptr, nullptr, nullptr, nullptr, $5, nullptr, line_num);
        add_to_syntax_tree(line_to_add, $4-1);
        $$ = line_to_add;
    }
    | TOKEN_WHILE expr TOKEN_COLON TOKEN_NEWLINE indent fill_line
    {  
        if(!check_indent_levels()){
            std::cout<<"Line "<<line_num-2<<": Indentation level does not match specification for a while loop\n";
            exit(1);
        }
        if(scope_stack[$5-1].second[0]) scope_stack[$5-1].second[0] = false;
        scope_stack[$5].second[1] = true;
        Line *line_to_add = new Line(LINE_WHILE, std::string(), nullptr, nullptr, $2, nullptr, $6, nullptr, line_num);
        add_to_syntax_tree(line_to_add, $5-1);
        $$ = line_to_add;
    }
    | TOKEN_RETURN expr
    {
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        Line *line_to_add = new Line(LINE_RETURN, std::string(), nullptr, nullptr, $2, nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);    
        $$ = line_to_add;
    }
    | loop_control
    { 
        if(scope_stack.back().second[0]) scope_stack.back().second[0] = false;
        if(!loop_available()){
            std::cout<<"Line "<<line_num<<": Loop not defined\n";
            exit(1);
        }
        $$ = $1;
    }
    ;

loop_control: TOKEN_CONTINUE 
            {
                Line *line_to_add = new Line(LINE_CONTINUE, std::string(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, line_num);
        add_to_syntax_tree(line_to_add, -1);    
                $$ = line_to_add;
            }
            | TOKEN_BREAK
            {
                Line *line_to_add = new Line(LINE_BREAK, std::string(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, line_num);
                add_to_syntax_tree(line_to_add, -1);    
                $$ = line_to_add;
            }
            ;

expr	: name TOKEN_ASSIGN expr_or
		{
            Expr *name = new Expr(EXPR_NAME, $1, line_num);
            Expr *e = new Expr(EXPR_ASSIGN, name, $3, line_num);
            $$ = e;
        }
        | expr TOKEN_INCEQ expr_or
		{
            Expr *e = new Expr(EXPR_PLUS_EQ, $1, $3, line_num);
            $$ = e;
        }
		| expr TOKEN_DECEQ expr_or
		{
            Expr *e = new Expr(EXPR_SUB_EQ, $1, $3, line_num);
            $$ = e;
        }
		| expr TOKEN_MULTEQ expr_or
		{
            Expr *e = new Expr(EXPR_MUL_EQ, $1, $3, line_num);
            $$ = e;
        }
		| expr TOKEN_DIVEQ expr_or
		{
            Expr *e = new Expr(EXPR_DIV_EQ, $1, $3, line_num);
            $$ = e;
        }
        | expr_or
		{
            $$ = $1;
        }
        ;

expr_or	: expr_or TOKEN_OR expr_and
		{
            Expr *e = new Expr(EXPR_OR, $1, $3, line_num);
            $$ = e;
        }
		| expr_and
		{
            $$ = $1;
        }
		;
		
expr_and: expr_and TOKEN_AND expr_eq
		{
            Expr *e = new Expr(EXPR_AND, $1, $3, line_num);
            $$ = e;
        }
		| expr_eq
		{
            $$ = $1;
        }
		;

expr_eq	: expr_eq TOKEN_EQ expr_comp
		{
            Expr *e = new Expr(EXPR_EQ, $1, $3, line_num);
            $$ = e;
        }
        | expr_eq TOKEN_NE expr_comp
		{
            Expr *e = new Expr(EXPR_NEQ, $1, $3, line_num);
            $$ = e;
        }
		| expr_comp
		{
            $$ = $1;
        }
		;

expr_comp   : expr_comp TOKEN_LT expr_add
		    {
                Expr *e = new Expr(EXPR_LT, $1, $3, line_num);
                $$ = e;
            }
		    | expr_comp TOKEN_LE expr_add
		    {
                Expr *e = new Expr(EXPR_LTE, $1, $3, line_num);
                $$ = e;
            }
		    | expr_comp TOKEN_GT expr_add
		    {
                Expr *e = new Expr(EXPR_GT, $1, $3, line_num);
                $$ = e;
            }
		    | expr_comp TOKEN_GE expr_add
		    {
                Expr *e = new Expr(EXPR_GTE, $1, $3, line_num);
                $$ = e;
            }
		    | expr_add
		    {
                $$ = $1;
            }
            ;

expr_add: expr_add TOKEN_ADD expr_mul
		{
            Expr *e = new Expr(EXPR_ADD, $1, $3, line_num);
            $$ = e;
        }
		| expr_add TOKEN_MINUS expr_mul
		{
            Expr *e = new Expr(EXPR_SUB, $1, $3, line_num);
            $$ = e;
        }
		| expr_mul
		{
            $$ = $1;
        }
		;

expr_mul: expr_mul TOKEN_MULTIPLY expr_exp
		{
            Expr *e = new Expr(EXPR_MUL, $1, $3, line_num);
            $$ = e;
        }
	 	| expr_mul TOKEN_DIVIDE expr_exp
		{
            Expr *e = new Expr(EXPR_DIV, $1, $3, line_num);
            $$ = e;
        }
		| expr_mul TOKEN_MOD expr_exp
		{
            Expr *e = new Expr(EXPR_MOD, $1, $3, line_num);
            $$ = e;
        }
		| expr_exp
		{
            $$ = $1;
        }
		;

expr_exp: expr_exp TOKEN_EXPONENT expr_bool
		{
            Expr *e = new Expr(EXPR_EXP, $1, $3, line_num);
            $$ = e;
        }
		| expr_bool
		{
            $$ = $1;
        }
		;

expr_bool   : TOKEN_NOT non_int_literal
		    {
                Expr *e = new Expr(EXPR_NOT, nullptr, $2, line_num);
                $$ = e;
            }
		    | TOKEN_NOT name
		    {
                Expr *name = new Expr(EXPR_NAME, $2, line_num);
                Expr *e = new Expr(EXPR_NOT, nullptr, name, line_num);
                $$ = e;
            }
		    | non_int_literal {
                $$ = $1;
            }
		    | expr_minus
		    {
                $$ = $1;
            }
		    ;

expr_minus	: TOKEN_MINUS expr_int
		    {
                Expr *e = new Expr(EXPR_NEG, nullptr, $2, line_num);
                $$ = e;
            }
		    | expr_int
		    {
                $$ = $1;
            }
		    ;

expr_int: value_literals
		{
            $$ = $1;
        }
		| expr_inc
		{
            $$ = $1;
        }
		;		

expr_inc: expr_inc TOKEN_INCREMENT
		{
            Expr *e = new Expr(EXPR_INC, $1, nullptr, line_num);
            $$ = e;
        }
        | expr_inc TOKEN_DECREMENT
		{
            Expr *e = new Expr(EXPR_DEC, $1, nullptr, line_num);
            $$ = e;
        }
		| expr_grp
		{
            $$ = $1;
        }
		;

expr_grp: TOKEN_LEFT_PAREN expr TOKEN_RIGHT_PAREN
		{
            $$ = $2;
        }
        | name
        {
            Expr *name = new Expr(EXPR_NAME, *$1, line_num);
            $$ = name;
        }
		| name TOKEN_LEFT_PAREN expr_list TOKEN_RIGHT_PAREN
        {
            Expr *name = new Expr(EXPR_NAME, *$1, line_num);
            Expr *e = new Expr(EXPR_CALL, name, $3, line_num);
            $$ = e;
        }
        ;

expr_list   : expr TOKEN_COMMA expr_list
            {
                Expr *e = new Expr(EXPR_ARG, $1, $3, line_num);
                $$ = e;
            }
            | expr
            { 
                Expr *e = new Expr(EXPR_ARG, $1, nullptr, line_num);
                $$ = e;
            }
            | /*empty*/
            { $$ = nullptr; }
            ;

indent  : TOKEN_INDENT_TAB
        { 
            if(!ws_define){
                spaces = false; 
                ws_define = true;
            }
            if(spaces){
                std::cout<<line_num<<": Mismatched tabs and spaces\n";
                exit(1);
            }
            max_stack_size++;
            int indent_level = check_indents(*$1) - 1;
            indent_levels_add(indent_level+1);
            $$ = indent_level+1;
        }
        | TOKEN_INDENT_SPACE
        { 
            if(!ws_define){
                spaces = true; 
                ws_define = true;
            }
            if(!spaces){
                std::cout<<line_num<<": Mismatched tabs and spaces\n";
                exit(1);
            }
            max_stack_size++;
            int indent_level = check_indents(*$1) - 1;
            indent_levels_add(indent_level+1);
            $$ = indent_level+1;
        }
        ;

begin_indent: TOKEN_INDENT_TAB
            {   
                if(!ws_define){
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
            {   
                if(!ws_define){
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
                    tails.pop_back();
                }
                indent_levels_add(0);
                max_stack_size = 1;
                $$ = 0;
            }
            ;

arg_list: name TOKEN_COMMA arg_list
        {
            Expr *name = new Expr(EXPR_NAME, *$1, line_num);
            Expr *e = new Expr(EXPR_ARG, name, $3, line_num);
            $$ = e;
        }
        | name
        {
            Expr *e = new Expr(EXPR_NAME, *$1, line_num);
            $$ = e; 
        }
        | /*empty*/
        { }
        ;

value_literals  : TOKEN_INTEGER_LITERAL
                {
                    Expr *e = new Expr(EXPR_INT_LITERAL, stoi(*$1), line_num);
                    $$ = e;
                }
                | TOKEN_FP_LITERAL
                {
                    Expr *e = new Expr(EXPR_FP_LITERAL, std::stod(*$1), line_num);
                    $$ = e;
                }
                ;

non_int_literal : TOKEN_BOOL_LITERAL
                {
                    bool value = (*$1 == "true") ? true : false;
                    Expr *e = new Expr(EXPR_BOOL_LITERAL, value, line_num);
                    $$ = e;
                }
                | TOKEN_STRING_LITERAL
                {
                    Expr *e = new Expr(EXPR_STRING_LITERAL, new std::string(*$1), line_num);
                    $$ = e;
                }
                ;

name: TOKEN_IDENTIFIER
    {
        std::string *item = new std::string(*$1);
        $$ = item;
    }
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
            tails.pop_back();
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
        tails.push_back(nullptr);
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

void add_to_syntax_tree(Line *l, int level){
        switch(l->kind){
            case LINE_PRINT:
            case LINE_RETURN:
            case LINE_BREAK:
            case LINE_PASS:
            case LINE_EXPR:
            case LINE_CONTINUE:
            case LINE_VAR_DEF:
                if(tails.back()) tails.back()->next = l;
                tails.back() = l;
                break;
            case LINE_IF:
            case LINE_FOR:
            case LINE_WHILE:
            case LINE_FUNC_DEF:
                if(tails[level]) tails[level]->next = l;
                tails[level] = l;
                break;
            case LINE_ELSE_IF:
            case LINE_ELSE:
                Line *nested = tails[level];
                while(nested->else_body) nested = nested->else_body;
                nested->else_body = l;
                break;
        }
}

void yy::Parser::error(const yy::location& l, const std::string& m){
    std::cout<<"Line: "<<line_num<<" "<<m<<std::endl;
    driver.error(l, m);
}
