%{
#include "tokens.h"
int line_num = 1;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
WS [ \t]
%%
{WS}
if { return TOKEN_IF; }
else { return TOKEN_ELSE; }
for { return TOKEN_FOR; }
while { return TOKEN_WHILE; }
return { return TOKEN_RETURN; }
function { return TOKEN_FUNCTION; }
print { return TOKEN_PRINT; }
and { return TOKEN_AND; }
or { return TOKEN_OR; }
not { return TOKEN_NOT; }
in { return TOKEN_IN; }
(true|false) { return TOKEN_BOOL_LITERAL; }
{DIGIT}+\.{DIGIT}* { return TOKEN_FP_LITERAL; }
{DIGIT}+ {return TOKEN_INTEGER_LITERAL; }
({LETTER}|_)({LETTER}|{DIGIT}|_)* { return TOKEN_IDENTIFIER; }
\( { return TOKEN_LEFT_PAREN; }
\) { return TOKEN_RIGHT_PAREN; }
\[ { return TOKEN_LEFT_BRACKET; }
\] { return TOKEN_RIGHT_BRACKET; }
\{ { return TOKEN_LEFT_BRACE; }
\} { return TOKEN_RIGHT_BRACE; }
\+\+ { return TOKEN_INCREMENT; }
\-\- { return TOKEN_DECREMENT; }
\+= { return TOKEN_INCEQ; }
\-= { return TOKEN_DECEQ; }
\*= { return TOKEN_MULTEQ; }
\\= { return TOKEN_DIVEQ; }
\* { return TOKEN_MULTIPLY; }
\/ { return TOKEN_DIVIDE; }
% { return TOKEN_MOD; }
\+ { return TOKEN_ADD; }
\- { return TOKEN_MINUS; }
\< { return TOKEN_LT; }
\<= { return TOKEN_LE; }
\> { return TOKEN_GT; }
\>= { return TOKEN_GE; }
= { return TOKEN_ASSIGN; }
== { return TOKEN_EQ; }
!= { return TOKEN_NE; }
: { return TOKEN_COLON; }
\n { line_num++; return TOKEN_NEWLINE; }
, { return TOKEN_COMMA; }
. { return TOKEN_ERROR; }
%%
int yyFlexLexer::yywrap(){
    return 1;
}
