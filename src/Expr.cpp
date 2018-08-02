#include "Expr.h"
#include "Symbol.h"
#include "SymbolTable.h"
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

bool Expr::check_side_effects(bool top){
    bool result = false;
    switch(kind){
        case EXPR_INC:
            result = true;
            break;
        case EXPR_DEC:
            result = true;
            break;
        default:
            break;
    }
    if(left) result = result || left->check_side_effects(false);
    if(right) result = result || right->check_side_effects(false);
    return result;
}

// Back trace dependencies to find circular or undefined dependency
// Alter to pass throug a set of checked good values and checked values.  Baiscally a depth first search
bool Expr::dependency_resolve(SymbolTable *table, std::set<std::string> 
    &checked_symbols, std::set<std::string> &good_symbols){
    Symbol *sym;
    bool fully_defined = true;
    bool result;
    bool right_result = true;
    bool left_result = true;
    switch(kind){
        case EXPR_NAME:
            if(checked_symbols.find(name) != checked_symbols.end()){
                if(good_symbols.find(name) != good_symbols.end()){
                    return true;
                }
                else{
                    std::cerr<<"ocl: line "<<line_num<<": ERROR: circular definition for symbol "<<name<<" at line "<<line_num<<std::endl;
                    return false;
                }
            }
            sym = table->search_table(name);
            if(!sym || sym->def_number < 0){
                std::cerr<<"ocl: line "<<line_num<<": ERROR: evaluation impossible due to undefined values "<<name<<" at line "<<line_num<<std::endl;
                return false;
            }
            checked_symbols.insert(name);
            for(std::vector<struct iter_info *>::iterator iter = 
                sym->iter_info.end() - 1; iter != 
                sym->iter_info.end() - sym->working_set - 1;iter--){
                if((*iter)->def_or_expr){
                    result = (*iter)->definition->dependency_resolve(table, 
                        checked_symbols, good_symbols);
                    if(!result){
                        std::cerr<<"ocl: line "<<line_num<<": ERROR: incomplete definition detected for variable "<<name<<" used at line "<<line_num<<" and defined at line "<<(*iter)->definition->line_num<<std::endl;
                        return false;
                    }
                }
            }
            good_symbols.insert(name);
            break;
        default:
            break;
    }
    if (left) left_result =
        left->dependency_resolve(table, checked_symbols, good_symbols);
    if (right) right_result =
        right->dependency_resolve(table, checked_symbols, good_symbols);
    return fully_defined && left_result && right_result;
}
