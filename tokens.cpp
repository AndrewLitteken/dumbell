/* token.c
 * Andrew Litteken
 * Switch statements for token ID in scanner
 * 2017-09-15
 * */
#include "tokens.h"
#include <string>
using namespace std;

// Used to convert token to string
string token_name(token_t t){ 
    switch (t) {
        case TOKEN_COMMENT: return  "COMMENT";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_INTEGER_LITERAL: return "INTEGER_LITERAL";
        case TOKEN_FP_LITERAL: return "FLOATING_POINT_LITERAL";
        case TOKEN_BOOL_LITERAL: return "BOOLEAN_LITERAL";
		case TOKEN_RIGHT_PAREN: return "RIGHT_PAREN";
		case TOKEN_LEFT_PAREN: return "LEFT_PAREN";
		case TOKEN_RIGHT_BRACKET: return "RIGHT_BRACKET";
		case TOKEN_LEFT_BRACKET: return "LEFT_BRACKET";
        case TOKEN_INCREMENT: return "INCREMENT";
		case TOKEN_DECREMENT: return "DECREMENT";
        case TOKEN_INCEQ: return "INCREMENT EQUALS";
		case TOKEN_MULTEQ: return "MUTLIPY EQUALS";
		case TOKEN_DIVEQ: return "DIVIDE EQUALS";
		case TOKEN_NOT: return "NOT";
		case TOKEN_EXPONENT: return "EXPONENT";
		case TOKEN_MULTIPLY: return "MULTIPLY";
		case TOKEN_DIVIDE: return "DIVIDE";
		case TOKEN_MOD: return "MODULOUS";
		case TOKEN_ADD: return "ADD";
		case TOKEN_MINUS: return "MINUS";
		case TOKEN_LT: return "LT";
		case TOKEN_LE: return "LE";
		case TOKEN_GT: return "GT";
		case TOKEN_GE: return "GE";
		case TOKEN_EQ: return "EQUAL";
		case TOKEN_NE: return "NOT_EQUAL";
		case TOKEN_AND: return "AND";
		case TOKEN_OR: return "OR";
		case TOKEN_ASSIGN: return "ASSIGN";
		case TOKEN_PRINT: return "PRINT";
		case TOKEN_FUNCTION: return "FUNCTION";
		case TOKEN_FOR: return "FOR";
		case TOKEN_IF: return "IF";
		case TOKEN_IN: return "IN";
        case TOKEN_ELSE: return "ELSE";
		case TOKEN_RETURN: return "RETURN";
		case TOKEN_WHILE: return "WHILE";
		case TOKEN_COLON: return "COLON";
		case TOKEN_LEFT_BRACE: return "LEFT_BRACE";
		case TOKEN_RIGHT_BRACE: return "RIGHT_BRACE";
		case TOKEN_COMMA: return "COMMA";
		case TOKEN_NEWLINE: return "NEWLINE";
        default:
            break;
    }   
    return "ERROR";
}
