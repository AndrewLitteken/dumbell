#include "expr.h"
#include <iostream>
#include <string>


Expr::Expr(expr_t k, Expr *l, Expr *r, int ln) {
	kind = k;
	left = l;
	right = r;
	name = std::string();
	literal_value = (int) NULL;
    literal_fp_value = (double) NULL;
	string_literal = std::string();
    line_num = ln;
}


Expr::Expr(expr_t k, const std::string s, int ln) {
    kind = k;
    if(k == EXPR_NAME) {
        name = s;
        string_literal = std::string();
    }
    else {
        string_literal = s;
        name = std::string();
    }
    literal_value = (int) NULL;
    left = nullptr;
    right = nullptr;
    literal_fp_value = (double) NULL;
    line_num = ln;
}

Expr::Expr(expr_t k, int i, int ln) {
    kind = k;
    literal_value = i;
    left = nullptr;
    right = nullptr;
    literal_fp_value = (double) NULL;
    name = std::string();
    string_literal = std::string();
}

Expr::Expr(expr_t k, bool i, int ln) {
    kind = k;
    literal_value = (int) i;
    left = nullptr;
    right = nullptr;
    literal_fp_value = (double) NULL;
    name = std::string();
    string_literal = std::string();
}

Expr::Expr(expr_t k, double d, int ln) {
    kind = k;
    literal_value = (int) NULL;
    left = nullptr;
    right = nullptr;
    literal_fp_value = d;
    name = std::string();
    string_literal = std::string();
}

Expr::~Expr(void) {

}
