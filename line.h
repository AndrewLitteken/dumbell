#ifndef LINE_H
#define LINE_H

#include "expr.h"
#include "type.h"
#include <string>

typedef enum {
    LINE_VAR_DEF,
    LINE_FUNC_DEF,
    LINE_EXPR,
    LINE_IF_ELSE,
    LINE_FOR,
    LINE_WHILE,
    LINE_PRINT,
    LINE_BREAK,
    LINE_PASS,
    LINE_CONTINUE
} line_t;

class Line {
    public:
        Line(line_t, std::string, Type *, Expr*, Expr *, Expr *, Line *, Line *, int); 
        ~Line();
        line_t kind;
        std::string name;
        Type *type;
        Expr *init_expr;
        Expr *expr;
        Line *body;
        Line *else_body;
        Line *next;
        int line_num;
};

#endif
