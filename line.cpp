#include "line.h"
#include "expr.h"
#include "type.h"
#include <string>

Line::Line(line_t l, std::string s, Type * t, Expr* ie, Expr *e, Expr *ne, Line *b, Line *eb, int ln){
    kind = l;
    name = s;
    type = t;
    init_expr = ie;
    expr = e;
    next_expr = ne;
    body = b;
    else_body = eb;
    line_num = ln;
}

Line::~Line(){}
