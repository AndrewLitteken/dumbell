#include "Expr.h"
#include "Type.h"
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
    if(k != EXPR_NAME){
        type = new Type(TYPE_STRING, nullptr, nullptr);
    }
}

Expr::Expr(expr_t k, int i, int ln) {
    kind = k;
    literal_value = i;
    left = nullptr;
    right = nullptr;
    literal_fp_value = (double) NULL;
    name = std::string();
    string_literal = std::string();
    type = new Type(TYPE_INTEGER, nullptr, nullptr);
}

Expr::Expr(expr_t k, bool i, int ln) {
    kind = k;
    literal_value = (int) i;
    left = nullptr;
    right = nullptr;
    literal_fp_value = (double) NULL;
    name = std::string();
    string_literal = std::string();
    type = new Type(TYPE_BOOL, nullptr, nullptr);
}

Expr::Expr(expr_t k, double d, int ln) {
    kind = k;
    literal_value = (int) NULL;
    left = nullptr;
    right = nullptr;
    literal_fp_value = d;
    name = std::string();
    string_literal = std::string();
    type = new Type(TYPE_FLOAT, nullptr, nullptr);
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
            if(sym == nullptr || sym->defined == false){
                std::cerr<<"ocl: line "<<line_num<<": ERROR: evaluation impossible due to undefined values "<<name<<" at line "<<line_num<<std::endl;
                return false;
            }
            checked_symbols.insert(name);
            if(sym->def_or_expr == true){
                result = sym->definition->dependency_resolve(table, 
                    checked_symbols, good_symbols);
                if(!result){
                    std::cerr<<"ocl: line "<<line_num<<": ERROR: incomplete definition detected for variable "<<name<<" used at line "<<line_num<<" and defined at line "<<sym->definition->line_num<<std::endl;
                    return false;
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

expr_t Expr::match_type(Expr *l, Expr *r){
    switch(l->kind){
        case EXPR_INT_LITERAL:
        case EXPR_FP_LITERAL:
            if(r->kind == EXPR_INT_LITERAL) return l->kind;
            else if(r->kind == EXPR_FP_LITERAL) return r->kind;
            else return EXPR_NOT_MATCH;
            break;
        default:
            if(l->kind == r->kind) return EXPR_NOT_MATCH;
            else return l->kind;
            break;
    }
    return EXPR_NOT_MATCH;
}

Expr * Expr::evaluate(SymbolTable *table){
    Expr *left_result = nullptr;
    Expr *right_result = nullptr;
    if(kind != EXPR_ASSIGN){
        if (left) left_result = left->evaluate(table);
        if (right) right_result = right->evaluate(table);
    }
    Expr *return_expr = nullptr;
    expr_t result;
    Symbol * symbol;
    bool resolved;
    std::string *new_str;
    std::set<std::string> checked_symbols;
    std::set<std::string> good_symbols;
    switch(kind){
        case EXPR_NAME:
            resolved = dependency_resolve(table, checked_symbols, good_symbols);
            if(resolved == false) return nullptr;
            symbol = table->search_table(name);
            if(!symbol) return nullptr;
            if(symbol->def_or_expr == true){
                return_expr = symbol->definition->evaluate(table);
            }
            else {
                return_expr = symbol->definition;
            }
            break;
        case EXPR_ADD:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(result == EXPR_NOT_MATCH) return nullptr;
            if(result != EXPR_INT_LITERAL && result != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_value + right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(result, left_result->literal_value + right_result->literal_fp_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_fp_value + right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(result, left_result->literal_fp_value + right_result->literal_fp_value, left_result->line_num);
            break;
        case EXPR_SUB:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(result == EXPR_NOT_MATCH) return nullptr;
            if(result != EXPR_INT_LITERAL && result != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_value - right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(result, left_result->literal_value - right_result->literal_fp_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_fp_value - right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(result, left_result->literal_fp_value - right_result->literal_fp_value, left_result->line_num);
            break;
        case EXPR_MUL:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_INT_LITERAL && left_result->kind != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_value * right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(result, left_result->literal_value * right_result->literal_fp_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_fp_value * right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(result, left_result->literal_fp_value * right_result->literal_fp_value, left_result->line_num);
            break;
        case EXPR_DIV:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_INT_LITERAL && left_result->kind != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_value / right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(result, left_result->literal_value / right_result->literal_fp_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_fp_value / right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(result, left_result->literal_fp_value / right_result->literal_fp_value, left_result->line_num);
			break;
        case EXPR_MOD:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_INT_LITERAL && left_result->kind != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(result, left_result->literal_value % right_result->literal_value, left_result->line_num);
            else {
                return nullptr;
            }
            break;
        case EXPR_ASSIGN:
            resolved = right->dependency_resolve(table, checked_symbols, good_symbols);
            if(resolved == false) return nullptr;
            right_result = right->evaluate(table);
            symbol = table->search_table(left->name);
            if(!symbol){
                symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL : 
                    SYMBOL_GLOBAL;
                symbol = new Symbol(k, false, left->name, right_result, right_result->type, table);
                table->add_to_level(left->name, symbol);
            }
            else{
                symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL : 
                    SYMBOL_GLOBAL;
                symbol->redefine(k, false, right_result, right_result->type, table);
                table->add_to_level(left->name, symbol);
            }
            return_expr = right_result;
			break;
        case EXPR_INC_EQ:
			break;
        case EXPR_PLUS_EQ:
			break;
        case EXPR_SUB_EQ:
			break;
        case EXPR_MUL_EQ:
			break;
        case EXPR_DIV_EQ:
			break;
        case EXPR_OR:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_BOOL_LITERAL || right_result->kind != EXPR_BOOL_LITERAL) return nullptr;
            return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value || right_result->literal_value, left_result->line_num);
			break;
        case EXPR_AND:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_BOOL_LITERAL || right_result->kind != EXPR_BOOL_LITERAL) return nullptr;
            return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value && right_result->literal_value, left_result->line_num);
            break;
        case EXPR_EQ:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value == right_result->literal_value, left_result->line_num);
            break;
        case EXPR_NEQ:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value != right_result->literal_value, left_result->line_num);
			break;
        case EXPR_LT:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_INT_LITERAL && left_result->kind != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value < right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value < right_result->literal_fp_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value < right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value < right_result->literal_fp_value, left_result->line_num);
			break;
        case EXPR_LTE:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_INT_LITERAL && left_result->kind != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value <= right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value <= right_result->literal_fp_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value <= right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value <= right_result->literal_fp_value, left_result->line_num);
			break;
        case EXPR_GT:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_INT_LITERAL && left_result->kind != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value > right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value < right_result->literal_fp_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value > right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value > right_result->literal_fp_value, left_result->line_num);
			break;
        case EXPR_GTE:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(!result) return nullptr;
            if(left_result->kind != EXPR_INT_LITERAL && left_result->kind != EXPR_FP_LITERAL)
                return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value <= right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value <= right_result->literal_fp_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value <= right_result->literal_value, left_result->line_num);
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value <= right_result->literal_fp_value, left_result->line_num);
			break;
        case EXPR_EXP:
			break;
        case EXPR_NOT:
            if(right_result == nullptr) return nullptr;
            if(right_result->kind != EXPR_BOOL_LITERAL) return nullptr;
            return_expr = new Expr(EXPR_BOOL_LITERAL, !right_result->literal_value, right_result->line_num);
			break;
        case EXPR_NEG:
			break;
        case EXPR_INC:
			break;
        case EXPR_DEC:
			break;
        case EXPR_ARG:
			break;
        case EXPR_PRINT_LIST:
            new_str = new std::string("");
            switch(left_result->kind){
                case EXPR_STRING_LITERAL:
                    *new_str += left_result->string_literal;
                    break;
                case EXPR_INT_LITERAL:
                    *new_str += std::to_string(left_result->literal_value);
                    break;
                case EXPR_FP_LITERAL:
                    *new_str += std::to_string(left_result->literal_fp_value);
                    break;
                case EXPR_BOOL_LITERAL:
                    *new_str += std::string(left_result->literal_fp_value ? "true" : "false");
                    break;
                default:
                    return_expr = nullptr;
                    break;
            }
            if(right != nullptr){
                switch(right_result->kind){
                    case EXPR_STRING_LITERAL:
                        *new_str += right_result->string_literal;
                        break;
                    case EXPR_INT_LITERAL:
                        *new_str += std::to_string(right_result->literal_value);
                        break;
                    case EXPR_FP_LITERAL:
                        *new_str += std::to_string(right_result->literal_fp_value);
                        break;
                    case EXPR_BOOL_LITERAL:
                        *new_str += std::string(right_result->literal_fp_value ? "true" : "false");
                        break;
                    default:
                        return_expr = nullptr;
                        break;
                }
            }
            return_expr = new Expr(EXPR_STRING_LITERAL, *new_str, left->line_num);
            break;
        case EXPR_CALL:
			break;
        case EXPR_INT_LITERAL:
            return_expr = this;
			break;
        case EXPR_FP_LITERAL:
            return_expr = this;
			break;
        case EXPR_BOOL_LITERAL:
            return_expr = this;
			break;
        case EXPR_STRING_LITERAL:
            return_expr = this;
			break;
        default:
            break;
    }
    return return_expr;
}
