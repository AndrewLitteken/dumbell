#include "Line.h"
#include "Expr.h"
#include "Type.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include <string>
#include <iostream>

extern int error_val;

Line::Line(line_t l, Expr* s, Type * t, Expr* ie, Expr *e, Expr *ne, Line *b, Line *eb, int ln){
    kind = l;
    loc = s;
    type = t;
    init_expr = ie;
    expr = e;
    next_expr = ne;
    body = b;
    else_body = eb;
    line_num = ln;
}

Line::~Line(){}

void Line::evaluate(SymbolTable *table){
    Expr *result_expr;
    Line *curr;
    std::string name;
    switch(kind){
        case LINE_VAR_DEF:
            if(loc->kind == EXPR_NAME){
                name = loc->name;
                symbol = table->search_table(name);
                if(!symbol){
                    symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL : 
                        SYMBOL_GLOBAL;
                    symbol = new Symbol(k, true, name, expr, type, table);
                    table->add_to_level(name, symbol);
                }
                else{
                    symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL : 
                        SYMBOL_GLOBAL;
                    symbol->redefine(k, true, expr, type, table);
                    table->add_to_level(name, symbol);
                }
            }
            else {
                Expr *left_eval = loc->left->evaluate(table);
                Expr *curr_right_expr = loc->right;
                Expr *dereferenced = left_eval;
                list_item *item = nullptr;
                if(dereferenced->kind != EXPR_LIST){
                    std::cerr<<"dbl: Line "<<line_num<<": can only assign to dereference lists, not "<<print_kind(dereferenced->kind)<<std::endl;
                    error_val = 3;
                    return;
                }
                Expr *evaled = curr_right_expr->evaluate(table);
                if(evaled == nullptr) {
                    return;
                }
                if(evaled->kind != EXPR_INT_LITERAL){
                    std::cerr<<"dbl: Line "<<line_num<<": can only dereference lists with integer values"<<std::endl;
                    error_val = 3;
                    return;
                }
                if(evaled->literal_value >= dereferenced->size || evaled->literal_value < 0){
                    std::cerr<<"dbl: Line "<<line_num<<": index "<<evaled->literal_value<<" is out of range"<<std::endl;
                    error_val = 1;
                    return;
                }
                item = dereferenced->list.at(dereferenced->size - 1 - evaled->literal_value);
                *(item->e) = *expr;
                item->t = OTHER;
            }
            break;
        case LINE_FUNC_DEF:
            break;
        case LINE_EXPR:
            result_expr = expr->evaluate(table);
            if(error_val != 0) return;
            break;
        case LINE_IF:
        case LINE_ELSE_IF:
            result_expr = expr->evaluate(table);
            if(error_val != 0) return;
            if(result_expr->type->kind != TYPE_BOOL){
                std::cerr<<"dbl: Line "<<line_num<<": if statement must act on a boolean value"<<std::endl;
                error_val = 4;
                return;
            }
            if(result_expr->literal_value == 1){
                table->add_level();
                curr = body;
                while(curr){
                    if(curr->kind != LINE_ELSE || curr->kind != LINE_ELSE_IF){
                        curr->evaluate(table);
                        if(error_val != 0) return;
                    }
                    curr = curr->next;
                }
                table->exit_level();
            }
            else{
                if(else_body != nullptr){
                    else_body->evaluate(table);
                    if(error_val != 0) return;
                }
            }
            break;
        case LINE_ELSE:
            table->add_level();
            curr = body;
            while(curr){
                if(curr->kind != LINE_ELSE || curr->kind != LINE_ELSE_IF){
                    curr->evaluate(table);
                    if(error_val != 0) return;
                }
                curr = curr->next;
            }
            table->exit_level();
            break;
        case LINE_FOR:
            break;
        case LINE_WHILE:
            result_expr = expr->evaluate(table);
            if(error_val != 0) return;
            if(result_expr->type->kind != TYPE_BOOL) {
                std::cerr<<"dbl: Line "<<line_num<<": while loop must act on a boolean value"<<std::endl;
                error_val = 4;
                return;
            }
            while(result_expr->literal_value == 1){
                table->add_level();
                curr = body;
                while(curr){
                    curr->evaluate(table);
                    if(error_val != 0) return;
                    curr = curr->next;
                }
                table->exit_level();
                result_expr = expr->evaluate(table);
                if(error_val != 0) return;
                if(result_expr->type->kind != TYPE_BOOL){
                    std::cerr<<"dbl: Line "<<line_num<<": while loop must act on a boolean value"<<std::endl;
                    error_val = 4;
                    return;
                }
            }
            break;
        case LINE_PRINT:
            result_expr = expr->evaluate(table);
            if(error_val != 0) return;
            if(result_expr == nullptr) return;
            switch (result_expr->kind){
                case EXPR_INT_LITERAL:
                    std::cout<<result_expr->literal_value;
                    break;
                case EXPR_FP_LITERAL:
                    std::cout<<result_expr->literal_fp_value;
                    break;
                case EXPR_BOOL_LITERAL:
                    std::cout<<(bool) result_expr->literal_value;
                    break;
                case EXPR_STRING_LITERAL:
                    std::cout<<result_expr->string_literal;
                    break;
                default:
                    std::cout<<"dbl: Line "<<line_num<<": no string representation for "<<print_kind(result_expr->kind)<<std::endl;
                    break;
            }
            break;
        case LINE_RETURN:
            break;
        case LINE_BREAK:
            break;
        case LINE_PASS:
            return;
            break;
        case LINE_CONTINUE:
            return;
            break;
        default:
            break;
    }
}

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

void Line::print_name(int tabs){
    for(int i = 0;i<tabs;i++) std::cout<<"  ";
    switch(kind){
        case LINE_VAR_DEF:
            std::cout<<symbol->base_name<<" at line "<<line_num<<": "<<symbol->base_name<<std::endl;
            std::cout<<"Dependent Definition: ";
            //symbol->printed = 1;
            for(std::set<std::string>::iterator dependents =      
                symbol->dependents->begin();dependents != 
                symbol->dependents->end();dependents++){
                std::cout<<*dependents;
                if (dependents != std::prev(symbol->dependents->end()))
                    std::cout<<", ";
            }
            std::cout<<std::endl;
            std::cout<<"-------------------"<<std::endl;
            break;
        case LINE_FUNC_DEF:
            break;
        case LINE_EXPR :
            /*if(expr->kind == EXPR_ASSIGN) {
                std::cout<<symbol->base_name<<" at line "<<line_num<<": "<<symbol->base_name<<std::endl;
                std::cout<<"Dependent Definitions: ";
                //symbol->printed = 1;
                for(std::set<std::string>::iterator dependents =      
                    symbol->dependents->begin();dependents != 
                    symbol->dependents->end();dependents++){
                    std::cout<<*dependents;
                    if (dependents != std::prev(symbol->dependents->end()))
                        std::cout<<", ";
                }
                std::cout<<std::endl;
                std::cout<<"-------------------"<<std::endl;
            }*/
            break;
        case LINE_IF:
            break;
        case LINE_WHILE:
            break;
        case LINE_PRINT:
            break;
        case LINE_RETURN:
            break;
        case LINE_BREAK:
            break;
        case LINE_PASS:
            break;
        case LINE_CONTINUE:
            break;
        default:
            break;
    }
    if(next) next->print_name(tabs); 
}
