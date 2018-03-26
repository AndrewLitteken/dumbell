#include "line.h"
#include "expr.h"
#include "type.h"
#include <string>
#include <iostream>

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

void Line::print(int tabs){
    Line *l;
    for(int i = 0;i<tabs;i++) std::cout<<"  ";
    switch(kind){
        case LINE_VAR_DEF:
            std::cout<<"Variable Definition\n";
            if(expr->kind == EXPR_STRING_LITERAL){
                std::cout<<"STRING DEF\n";
            }
            break;
        case LINE_FUNC_DEF:
            std::cout<<"Function Definition\n";
            body->print(tabs+1);
            break;
        case LINE_EXPR:
            std::cout<<"Expression\n";
            if(expr->kind == EXPR_STRING_LITERAL){
                std::cout<<"STRING DEF\n";
            }
            break;
        case LINE_IF:
            std::cout<<"If\n";
            body->print(tabs+1);
            if(else_body){
                l = else_body;
                while(l->else_body){
                    for(int i = 0;i<tabs;i++) std::cout<<"  ";
                    std::cout<<"Else If\n";
                    l->body->print(tabs+1);
                    l = l->else_body;
                }
                if(l) {
                    for(int i = 0;i<tabs;i++) std::cout<<"  ";
                    if(l->kind==LINE_ELSE) std::cout<<"Else\n";
                    else std::cout<<"Else if\n";
                    l->body->print(tabs+1);
                }
            }
            break;
        case LINE_WHILE:
            std::cout<<"While\n";
            body->print(tabs+1);
            break;
        case LINE_PRINT:
            std::cout<<"Print\n"; 
            break;
        case LINE_RETURN:
            std::cout<<"Return\n";
            break;
        case LINE_BREAK:
            std::cout<<"Break\n";
            break;
        case LINE_PASS:
            std::cout<<"Pass\n";
            break;
        case LINE_CONTINUE:
            std::cout<<"Continue\n";
            break;
        default:
            break;
    }
    if(next) next->print(tabs);       
}
