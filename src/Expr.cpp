#include "Expr.h"
#include <iostream>
#include <string>
#include <set>

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

std::set<std::string>* Expr::get_expression_deps(){
    std::set<std::string> *d = new std::set<std::string>();
    if(left){
        std::set<std::string> t(*left->get_expression_deps());
        for(std::set<std::string>::iterator it = t.begin();it != t.end();
            it++){
            d->insert(*it);
        }
    }
    if(right){
        std::set<std::string> t(*right->get_expression_deps());
        for(std::set<std::string>::iterator it = t.begin();it != t.end();
            it++){
            d->insert(*it);
        }
    }
    if(kind == EXPR_NAME){
        d->insert(name);
    }
    return d;
}
