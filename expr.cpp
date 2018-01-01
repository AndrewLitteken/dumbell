#include "expr.h"


Expr::Expr(expr_t k, Expr *l, Expr *r, const std::string n, int lv, const std::string sl) {
	kind = k;
	left = l;
	right = r;
	name = n;
	literal_value = lv;
	string_literal = sl; 
}

Expr::~Expr(void) {

}
