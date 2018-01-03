#ifndef EXPR_H
#define EXPR_H

#include <string>

typedef enum {
	EXPR_ADD,
	EXPR_SUB,
	EXPR_MUL,
	EXPR_DIV,
	EXPR_ASSIGN,
	EXPR_INC_EQ,
	EXPR_PLUS_EQ,
	EXPR_SUB_EQ,
	EXPR_MUL_EQ,
	EXPR_DIV_EQ,
	EXPR_OR,
	EXPR_AND,
	EXPR_EQ,
	EXPR_NEQ,
	EXPR_LT,
	EXPR_LTE,
	EXPR_GT,
	EXPR_GTE,
	EXPR_MOD,
	EXPR_EXP,
	EXPR_NOT,
	EXPR_NEG,
	EXPR_INC,
	EXPR_DEC,
	EXPR_ARG,
	EXPR_CALL
} expr_t;

class Expr {
	public:
		Expr(expr_t, Expr *, Expr *, const std::string, int, const std::string);
		~Expr();
	private:
		expr_t kind;
		Expr *left;
		Expr *right;
		std::string name; 
		int literal_value;
		std::string string_literal;
};

#endif
