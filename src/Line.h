#ifndef LINE_H
#define LINE_H

#include "Expr.h"
#include "Type.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include <string>

typedef enum {
    LINE_VAR_DEF,
    LINE_FUNC_DEF,
    LINE_EXPR,
    LINE_IF,
    LINE_ELSE_IF,
    LINE_ELSE,
    LINE_FOR,
    LINE_WHILE,
    LINE_PRINT,
    LINE_RETURN,
    LINE_BREAK,
    LINE_PASS,
    LINE_CONTINUE
} line_t;

class Expr;
class Symbol;
class SymbolTable;

class Line {
    public:
        Line(line_t, Expr *e, Type *, Expr*, Expr *, Expr *, Line *, Line *, int); 
        ~Line();
        void print(int);
        void print_name(int);
        void name_resolve(SymbolTable *);
        void evaluate(SymbolTable *);
        line_t kind;
        Expr *loc;
        Symbol *symbol;
        Type *type;
        Expr *init_expr;
        Expr *expr;
        Expr *next_expr;
        Line *body;
        Line *else_body;
        Line *next;
        int line_num;
};

#endif
