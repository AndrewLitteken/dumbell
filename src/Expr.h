#ifndef EXPR_H
#define EXPR_H

#include "SymbolTable.h"
#include "Symbol.h"
#include <string>
#include <set>

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
	EXPR_CALL,
    EXPR_NAME,
    EXPR_INT_LITERAL,
    EXPR_FP_LITERAL,
    EXPR_BOOL_LITERAL,
    EXPR_STRING_LITERAL
} expr_t;

class Expr {
	public:
		Expr(expr_t, Expr *, Expr *, int);
		Expr(expr_t, const std::string, int);
        Expr(expr_t, int, int);
        Expr(expr_t, bool, int);
        Expr(expr_t, double, int);
        ~Expr();
		void print();
        std::set<std::string>* get_expression_deps();
        bool check_side_effects(bool);
        bool dependency_resolve(SymbolTable *, std::set<std::string> &,
            std::set<std::string> &);
        expr_t kind;
		Expr *left;
		Expr *right;
		std::string name; 
		int literal_value;
        double literal_fp_value;
		std::string string_literal;
        int line_num;
};

#endif
