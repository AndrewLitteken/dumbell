%{
#include "ocl-scanner.h"
#include <string>
#include <cstdlib>
#include <climits>
#include <cerrno>
int line_num = 1;

typedef yy::Parser::token token;
typedef yy::Parser::token_type token_type;

#define yyterminate() return token::TOKEN_EOF

#define YY_NO_UNISTD_H

%}
%option c++
%option yywrap nounput
%option debug
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

DIGIT [0-9]
LETTER [a-zA-Z]
WS [ \t]

%%
%{
    // reset location
    yylloc->step();
%}

^[\t]+ {yylval->str = new std::string(yytext, yyleng); return token::TOKEN_INDENT_TAB; }
^[ ]+ {yylval->str = new std::string(yytext, yyleng); return token::TOKEN_INDENT_SPACE; }
{WS}
; { return token::TOKEN_SEMI; }
if { return token::TOKEN_IF; }
else { return token::TOKEN_ELSE; }
for { return token::TOKEN_FOR; }
pass { return token::TOKEN_PASS; }
break { return token::TOKEN_BREAK; }
continue { return token::TOKEN_CONTINUE; }
while { return token::TOKEN_WHILE; }
return { return token::TOKEN_RETURN; }
function { return token::TOKEN_FUNCTION; }
print { return token::TOKEN_PRINT; }
and { return token::TOKEN_AND; }
or { return token::TOKEN_OR; }
not { return token::TOKEN_NOT; }
in { return token::TOKEN_IN; }
(true|false) { return token::TOKEN_BOOL_LITERAL; }
{DIGIT}*\.{DIGIT}* { return token::TOKEN_FP_LITERAL; }
{DIGIT}+ {return token::TOKEN_INTEGER_LITERAL; }
({LETTER}|_)({LETTER}|{DIGIT}|_)* { return token::TOKEN_IDENTIFIER; }
\( { return token::TOKEN_LEFT_PAREN; }
\) { return token::TOKEN_RIGHT_PAREN; }
\[ { return token::TOKEN_LEFT_BRACKET; }
\] { return token::TOKEN_RIGHT_BRACKET; }
\{ { return token::TOKEN_LEFT_BRACE; }
\} { return token::TOKEN_RIGHT_BRACE; }
\+\+ { return token::TOKEN_INCREMENT; }
\-\- { return token::TOKEN_DECREMENT; }
\+= { return token::TOKEN_INCEQ; }
\-= { return token::TOKEN_DECEQ; }
\*= { return token::TOKEN_MULTEQ; }
\\= { return token::TOKEN_DIVEQ; }
\* { return token::TOKEN_MULTIPLY; }
\/ { return token::TOKEN_DIVIDE; }
% { return token::TOKEN_MOD; }
\+ { return token::TOKEN_ADD; }
\- { return token::TOKEN_MINUS; }
\< { return token::TOKEN_LT; }
\<= { return token::TOKEN_LE; }
\> { return token::TOKEN_GT; }
\>= { return token::TOKEN_GE; }
:= { return token::TOKEN_DEFINITION; }
= { return token::TOKEN_ASSIGN; }
== { return token::TOKEN_EQ; }
!= { return token::TOKEN_NE; }
: { return token::TOKEN_COLON; }
\n { line_num++; return token::TOKEN_NEWLINE; }
, { return token::TOKEN_COMMA; }
. { return token::TOKEN_ERROR; }
%%

int yyFlexLexer::yylex()
{
    std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
    return 0;
}

yy::Scanner::Scanner(std::istream* in, std::ostream* out) : yyFlexLexer(in, out){
}

yy::Scanner::~Scanner(){}

void yy::Scanner::set_debug(bool b){
    yy_flex_debug = b;
}

int yyFlexLexer::yywrap(){
    return 1;
}
