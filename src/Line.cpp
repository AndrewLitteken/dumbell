#include "Line.h"
#include "Expr.h"
#include "Type.h"
#include "Symbol.h"
#include "SymbolTable.h"
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

/*void Line::name_resolve(SymbolTable *table){
    bool result;
    bool dependency_result;
    std::set<std::string> checked;
    std::set<std::string> good_symbols;
    switch(kind){
        case LINE_VAR_DEF:
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
            }
            symbol->working_set = 1;
            break;
        case LINE_EXPR:
            if(expr->kind == EXPR_ASSIGN){
                dependency_result = expr->right->dependency_resolve(table, checked, good_symbols);
                if(!dependency_result){
                    std::cerr<<"ocl: line "<<line_num<<": ERROR: Unable to resolve depedencies for expression to evaluate "<<expr->left->name<<" at line "<<line_num<<std::endl;
                }
                result = true;
            }
            else {
                dependency_result = expr->dependency_resolve(table, checked, good_symbols);
                result = expr->check_side_effects(true);
            }
            if(expr->kind == EXPR_ASSIGN){
                std::string n = expr->left->name;
                symbol = table->search_table(n);
                if(!symbol){
                    symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL                         : SYMBOL_GLOBAL;
                    symbol = new Symbol(k, false, n, expr, type, table);
                    table->add_to_level(n, symbol);
                }
                else{
                    symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL 
                        : SYMBOL_GLOBAL;
                    symbol->redefine(k, false, expr, type, table);
                }
                symbol->working_set = 1;
            }
            else if(result && (expr->kind != EXPR_INC && 
                expr->kind != EXPR_DEC)){
                std::cout<<"ocl: line "<<line_num<<": WARNING: part of expression at line "
                    <<line_num<<" has no effect on result of program"
                    <<std::endl;
            }
            else if(!result){
                std::cout<<"ocl: line "<<line_num<<": WARNING: Expression at line "<<line_num<<
                    " has no effect on result of program"<<std::endl;
            }
            break;
        case LINE_IF:
            //expr->name_resolve(table, true);
            //expr->dependency_resolve(table, checked, good_symbols);
            break;
        default:
            break;
    }

    if(next) next->name_resolve(table);
    return;
}*/

void Line::evaluate(SymbolTable *table){
    Expr *result_expr;
    Line *curr;
    switch(kind){
        case LINE_VAR_DEF:
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
            break;
        case LINE_FUNC_DEF:
            symbol = table->search_table(name);
            if(!symbol){
                symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL : 
                    SYMBOL_GLOBAL;
                symbol = new Symbol(k, false, name, expr, type, table);
                table->add_to_level(name, symbol);
            }
            else{
                symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL : 
                    SYMBOL_GLOBAL;
                symbol->redefine(k, false, expr, type, table);
                table->add_to_level(name, symbol);
            }
            break;
        case LINE_EXPR:
            result_expr = expr->evaluate(table);
            break;
        case LINE_IF:
        case LINE_ELSE_IF:
            result_expr = expr->evaluate(table);
            if(result_expr->type->kind != TYPE_BOOL) return;
            if(result_expr->literal_value == 1){
                table->add_level();
                curr = body;
                while(curr){
                    if(curr->kind != LINE_ELSE || curr->kind != LINE_ELSE_IF)
                        curr->evaluate(table);
                    curr = curr->next;
                }
                table->exit_level();
            }
            else{
                if(else_body != nullptr)
                    else_body->evaluate(table);
            }
            break;
        case LINE_ELSE:
            table->add_level();
            curr = body;
            while(curr){
                if(curr->kind != LINE_ELSE || curr->kind != LINE_ELSE_IF)
                    curr->evaluate(table);
                curr = curr->next;
            }
            table->exit_level();
            break;
        case LINE_FOR:
            break;
        case LINE_WHILE:
            result_expr = expr->evaluate(table);
            if(result_expr->type->kind != TYPE_BOOL) return;
            while(result_expr->literal_value == 1){
                table->add_level();
                curr = body;
                while(curr){
                    curr->evaluate(table);
                    curr = curr->next;
                }
                table->exit_level();
                result_expr = expr->evaluate(table);
                if(result_expr->type->kind != TYPE_BOOL) return;
            }
            break;
        case LINE_PRINT:
            result_expr = expr->evaluate(table);
            if(result_expr == nullptr) exit(1);
            switch (result_expr->type->kind){
                case TYPE_INTEGER:
                    std::cout<<result_expr->literal_value;
                    break;
                case TYPE_FLOAT:
                    std::cout<<result_expr->literal_fp_value;
                    break;
                case TYPE_BOOL:
                    std::cout<<(bool) result_expr->literal_value;
                    break;
                case TYPE_STRING:
                    std::cout<<result_expr->string_literal;
                    break;
                default:
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
