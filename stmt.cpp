#include "stmt.h"


Stmt::Stmt(stmt_t s, Decl *d, Expr *i, Expr *e, Expr *ne, Stmt *b, Stmt *eb, Stmt *n) {
	kind = s;
	decl = d;
	init_expr = i;
	expr = e;
	next_expr = ne;
	body = b;
	else_body = eb;
	next = n; 
}

Stmt::~Stmt(void) {

}
