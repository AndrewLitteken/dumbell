#ifndef EXPR_H
#define EXPR_H

#include "SymbolTable.h"
#include "Symbol.h"
#include "Type.h"
#include <string>
#include <set>
#include <vector>

class Expr;

typedef enum content_type {
	INT,
	STR,
	BOOL,
	OTHER
} content_type;

typedef struct list_item {
	Expr *e;
	content_type t;
} list_item;

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
	EXPR_PRINT_LIST,
	EXPR_CALL,
    EXPR_NAME,
    EXPR_INT_LITERAL,
    EXPR_FP_LITERAL,
    EXPR_BOOL_LITERAL,
    EXPR_STRING_LITERAL,
    EXPR_DEREF,
    EXPR_PROP,
    EXPR_LIST,
    EXPR_LIST_ITEM,
    EXPR_NOT_MATCH // only for type checking
} expr_t;

std::string print_kind(expr_t kind);

class Expr {
	public:
		Expr(expr_t, Expr *, Expr *, int);
		Expr(expr_t, const std::string, int);
		Expr(expr_t, Expr *, Expr *, const std::string, int);
        Expr(expr_t, int, int);
        Expr(expr_t, bool, int);
        Expr(expr_t, double, int);
        Expr(Expr *);
        ~Expr();
		void print();
        std::set<std::string>* get_expression_deps();
        bool check_side_effects(bool);
        bool dependency_resolve(SymbolTable *, std::set<std::string> &,
            std::set<std::string> &);
        Expr * evaluate(SymbolTable *);
        expr_t match_type(Expr *, Expr *);
        expr_t kind;
		Expr *left;
		Expr *right;
		Type *type;
		int size;
		std::string name; 
		int literal_value;
        double literal_fp_value;
		std::string string_literal;
		std::vector<list_item *> list;
        int line_num;
};

#endif
