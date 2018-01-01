#ifndef _INC_DECL
#define _INC_DECL
#include "decl.h"
#endif

#ifndef _INC_EXPR
#define _INC_EXPR
#include "expr.h"
#endif

typedef enum {
	STMT_DECL,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_WHILE,
	STMT_PRINT,
	STMT_BLOCK
} stmt_t;

class Stmt {
	public:
		Stmt(stmt_t, Decl*, Expr*, Expr*, Expr*, Stmt*, Stmt*, Stmt*);
		~Stmt();
	private:
		stmt_t kind;
		Decl *decl;
		Expr *init_expr;
		Expr *expr;
		Expr *next_expr;
		Stmt *body;
		Stmt *else_body;
		Stmt *next;
}
