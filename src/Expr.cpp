#include "Expr.h"
#include "Type.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <set>
#include <cmath>

extern int error_val;
int test = 0;

Expr::Expr(expr_t k, Expr *l, Expr *r, int ln) {
	kind = k;
	left = l;
	right = r;
	name = std::string();
	literal_value = (int) NULL;
    literal_fp_value = (double) NULL;
	string_literal = std::string();
    line_num = ln;
    size = -1;
    if(k == EXPR_LIST){
        size = 0;
        Expr *curr = l;
        while(curr){
            size++;
            curr = curr->right;
        }
    }
}

Expr::Expr(Expr *e){
    kind = e->kind;
    if(e->left) left = new Expr(e->left);
    else left = nullptr;
    if(e->right) right = new Expr(e->right);
    else right = nullptr;
    name = e->name;
    size = e->size;
    literal_value = e->literal_value;
    string_literal = e->string_literal;
    literal_fp_value = e->literal_fp_value;
    line_num = e->line_num;
    for(int i=0;i<e->list.size();i++){
        list_item *item = new list_item;
        item->e = e->list[i]->e;
        item->t = e->list[i]->t;
        list.push_back(item);
    }
}

Expr::~Expr(void) {
    if(left) delete left;
    if(right) delete right;
    for(int i = 0;i<list.size();i++){
        delete list[i];
    }
}

Expr::Expr(expr_t k, const std::string s, int ln) {
    kind = k;
    if(k == EXPR_NAME) {
        saved_sym = nullptr;
        name = s;
        string_literal = std::string();
        size = -1;
    }
    else {
        string_literal = s;
        name = std::string();
        size = s.length();
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

Expr::Expr(expr_t k, Expr *l, Expr *r, const std::string p, int ln) {
    kind = k;
    literal_value = (int) NULL;
    left = l;
    right = r;
    literal_fp_value = (double) NULL;
    line_num = ln;
    string_literal = p;
    size = -1;
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
    size = -1;
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
    size = -1;
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
    size = -1;
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

void Expr::replace(Expr *e, std::string name){
    if(left){
        if(left->kind == EXPR_NAME && left->name == name){
            left = new Expr(e);
        }
        else{
            left->replace(e, name);
        }
    }
    if(right){
        if(right->kind == EXPR_NAME && right->name == name){
            right = new Expr(e);
        }
        else{
            right->replace(e, name);
        }
    }
}

void Expr::partial_eval(SymbolTable *table){
    if(left){
        if(left->kind == EXPR_PART_EVAL){
            Expr *e = left->evaluate(table);
            if(e == nullptr) return;
            left = new Expr(e);
        }
        else{
            left->partial_eval(table);
        }
    }
    if(right){
        if(right->kind == EXPR_PART_EVAL){
            Expr *e = right->evaluate(table);
            if(e == nullptr) return;
            right = new Expr(e);
        }
        else{
            right->partial_eval(table);
        }
    }
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
                    std::cerr<<"dbl: line "<<line_num<<": ERROR: circular definition for symbol "<<name<<" at line "<<line_num<<std::endl;
                    return false;
                }
            }
            sym = table->search_table(name);
            if(sym == nullptr || sym->defined == false){
                std::cerr<<"dbl: line "<<line_num<<": ERROR: evaluation impossible due to undefined values "<<name<<" at line "<<line_num<<std::endl;
                return false;
            }
            checked_symbols.insert(name);
            if(sym->def_or_expr == true){
                result = sym->definition->dependency_resolve(table, 
                    checked_symbols, good_symbols);
                if(!result){
                    std::cerr<<"dbl: line "<<line_num<<": ERROR: incomplete definition detected for variable "<<name<<" used at line "<<line_num<<" and defined at line "<<sym->definition->line_num<<std::endl;
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
            if(l->kind != r->kind) return EXPR_NOT_MATCH;
            else return l->kind;
            break;
    }
    return EXPR_NOT_MATCH;
}

std::string print_kind(expr_t kind){
    std::string output;
    switch(kind){
        case EXPR_ADD:
            output = "addition";
			break;
        case EXPR_SUB:
            output = "subtraction";
			break;
        case EXPR_MUL:
            output = "multiplication";
			break;
        case EXPR_DIV:
            output = "division";
			break;
        case EXPR_ASSIGN:
            output = "assignment";
			break;
        case EXPR_OR:
            output = "or";
			break;
        case EXPR_AND:
            output = "and";
			break;
        case EXPR_EQ:
            output = "equals";
			break;
        case EXPR_NEQ:
            output = "not equals";
			break;
        case EXPR_LT:
            output = "less than";
			break;
        case EXPR_LTE:
            output = "less than or equal";
			break;
        case EXPR_GT:
            output = "greater than";
			break;
        case EXPR_GTE:
            output = "greater than or equal";
			break;
        case EXPR_MOD:
			output = "modulus";
            break;
        case EXPR_EXP:
            output = "exponent";
			break;
        case EXPR_NOT:
            output = "logical not";
			break;
        case EXPR_NEG:
            output = "unary negation";
			break;
        case EXPR_INC:
            output = "increment";
			break;
        case EXPR_DEC:
            output = "decrement";
			break;
        case EXPR_ARG:
            output = "argument";
			break;
        case EXPR_PRINT_LIST:
            output = "print list";
			break;
        case EXPR_CALL:
            output = "function call";
			break;
        case EXPR_NAME:
            output = "indentifier";
			break;
        case EXPR_INT_LITERAL:
            output = "integer";
			break;
        case EXPR_FP_LITERAL:
            output = "floating point";
			break;
        case EXPR_BOOL_LITERAL:
            output = "boolean";
			break;
        case EXPR_STRING_LITERAL:
            output = "string";
            break;
        case EXPR_DEREF:
            output = "derefrence";
            break;
        case EXPR_PROP:
            output = "property";
            break;
        case EXPR_LIST:
            output = "list";
            break;
        case EXPR_LIST_ITEM:
            output = "list item";
            break;
        case EXPR_PART_EVAL:
            output = "partial evaluation";
            break;
        default:
            break;
    }
    return output;
}

Expr * Expr::evaluate(SymbolTable *table){
    /*std::vector<Expr *> expr_stack;
    std::vector<std::pair<Expr *, Expr *>> rl_stack;
    expr_stack.push_back(this);
    rl_stack.push_back(std::pair<Expr *, Expr *>(nullptr, nullptr));*/
    Expr *left_result = nullptr;
    Expr *right_result = nullptr;
    if(kind != EXPR_ASSIGN){
        if (left){
            left_result = left->evaluate(table);
        }
        if (right){
            right_result = right->evaluate(table);  
        }
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
            if(saved_sym == nullptr){
                symbol = table->search_table(name);
                saved_sym = symbol;
            }
            else
                symbol = saved_sym;
            if(!symbol){
                std::cerr<<"dbl: symbol "<<name<<" undefined"<<std::endl;
                error_val = 1;
                return nullptr;
            }
            if(symbol->def_or_expr == true){
                resolved = dependency_resolve(table, checked_symbols, good_symbols);
                resolved = true;
                if(resolved == false) return nullptr;
                return_expr = new Expr(symbol->definition->evaluate(table));
            }
            else {
                return_expr = new Expr(symbol->definition);
            }
            break;
        case EXPR_ADD:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value + right_result->literal_value;
                delete right_result;
                return_expr = left_result;
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_value + right_result->literal_fp_value;
                delete right_result;
                return_expr = left_result;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_fp_value + right_result->literal_value;
                delete right_result;
                return_expr = left_result;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_fp_value + right_result->literal_fp_value;
                delete right_result;
                return_expr = left_result;
            }
            else if(left_result->kind == EXPR_LIST && right_result->kind == EXPR_LIST){
                return_expr = right_result;
                for(int i = 0;i < left_result->size;i++){
                    list_item *item = new list_item;
                    item->e = left_result->list[i]->e;
                    item->t = left_result->list[i]->t;
                    return_expr->size = return_expr->size + 1;
                    return_expr->list.push_back(item);
                }
                delete left_result;
            }
            else if(left_result->kind == EXPR_STRING_LITERAL && right_result->kind == EXPR_STRING_LITERAL){
                left_result->string_literal = left_result->string_literal + right_result->string_literal;
                delete right_result;
                return_expr = left_result;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<" are not compatible for addition"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            break;
        case EXPR_SUB:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value - right_result->literal_value;
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_value - right_result->literal_fp_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_fp_value - right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_fp_value - right_result->literal_fp_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<"are not compatible for subtraction"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            delete right_result;
            return_expr = left_result;
            break;
        case EXPR_MUL:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value * right_result->literal_value;
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_value * right_result->literal_fp_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_fp_value * right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_fp_value * right_result->literal_fp_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<"are not compatible for multiplication"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            delete right_result;
            return_expr = left_result;
            break;
        case EXPR_DIV:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value / right_result->literal_value;
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_value / right_result->literal_fp_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_fp_value / right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = left_result->literal_fp_value / right_result->literal_fp_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<"are not compatible for division"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            delete right_result;
            return_expr = left_result;
            break;
        case EXPR_MOD:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value % right_result->literal_value;
                delete right_result;
                return_expr = left_result;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<"are not compatible for modulus"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            break;
        case EXPR_ASSIGN:
            right_result = right->evaluate(table);
            if(right_result == nullptr) return nullptr;
            if(left->kind == EXPR_NAME){
                if(left->saved_sym == nullptr){
                    symbol = table->search_table(left->name);
                }
                else{
                    symbol = left->saved_sym;
                }
                if(!symbol){
                    symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL : 
                        SYMBOL_GLOBAL;
                    symbol = new Symbol(k, false, left->name, right_result, right_result->type, table);
                    left->saved_sym = symbol;
                    table->add_to_level(left->name, symbol);
                }
                else{
                    symbol_t k = table->current_level > 1 ? SYMBOL_INTERNAL : 
                        SYMBOL_GLOBAL;
                    symbol->redefine(k, false, right_result, right_result->type, table);
                }
            }
            else {
                Expr *left_eval = left->left->evaluate(table);
                Expr *curr_right_expr = left->right;
                Expr *dereferenced = left_eval;
                list_item *item = nullptr;
                while(curr_right_expr){
                    if(dereferenced->kind != EXPR_LIST){
                        std::cerr<<"dbl: Line "<<line_num<<": can only assign to dereference lists, not "<<print_kind(dereferenced->kind)<<std::endl;
                        error_val = 3;
                        return nullptr;
                    }
                    Expr *evaled = curr_right_expr->evaluate(table);
                    if(evaled == nullptr) {
                        return nullptr;
                    }
                    if(evaled->kind != EXPR_INT_LITERAL){
                        std::cerr<<"dbl: Line "<<line_num<<": can only dereference lists with integer values"<<std::endl;
                        error_val = 3;
                        return nullptr;
                    }
                    if(evaled->literal_value >= dereferenced->size || evaled->literal_value < 0){
                        std::cerr<<"dbl: Line "<<line_num<<": index "<<evaled->literal_value<<" is out of range"<<std::endl;
                        error_val = 1;
                        return nullptr;
                    }
                    item = dereferenced->list.at(dereferenced->size - 1 - evaled->literal_value);
                    dereferenced = item->e;
                    curr_right_expr = curr_right_expr->right;
                }
                *(item->e) = *right_result;
            }
            return_expr = right_result;
			break;
        case EXPR_OR:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_BOOL_LITERAL && right_result->kind == EXPR_BOOL_LITERAL){
                left_result->literal_value = left_result->literal_value || right_result->literal_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": type of "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<" not compatible for logical or"<<std::endl;
                error_val = 3;
                return nullptr;
            }
            delete right_result;
            return_expr = left_result;
			break;
        case EXPR_AND:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_BOOL_LITERAL && right_result->kind == EXPR_BOOL_LITERAL){
                left_result->literal_value = left_result->literal_value && right_result->literal_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": type of "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<" not compatible for logical and"<<std::endl;
                error_val = 3;
                return nullptr;
            }
            delete right_result;
            return_expr = left_result;
            break;
        case EXPR_EQ:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            return_expr = left_result;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL)
                return_expr->literal_value = left_result->literal_value == right_result->literal_value;
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr->literal_value = left_result->literal_value == right_result->literal_fp_value;
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL)
                return_expr->literal_value = left_result->literal_fp_value == right_result->literal_fp_value;
            else if(left_result->kind == EXPR_BOOL_LITERAL && right_result->kind == EXPR_BOOL_LITERAL)
                return_expr->literal_value = left_result->literal_value == right_result->literal_fp_value;
            else if(left_result->kind == EXPR_STRING_LITERAL && right_result->kind)
                return_expr->literal_value = left_result->string_literal == right_result->string_literal;
            else{
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<" are not compatible for equality"<<std::endl;
                return nullptr;
            }
            return_expr->kind = EXPR_BOOL_LITERAL;
            delete right_result;
            break;
        case EXPR_NEQ:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(result == EXPR_NOT_MATCH){
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<"are not compatible"<<std::endl;
                return nullptr;
            }
            if(result == EXPR_INT_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value != right_result->literal_value, left_result->line_num);
            else if(result == EXPR_FP_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->literal_fp_value != right_result->literal_fp_value, left_result->line_num);
            else if(result == EXPR_STRING_LITERAL)
                return_expr = new Expr(EXPR_BOOL_LITERAL, left_result->string_literal != right_result->string_literal, left_result->line_num);
			break;
        case EXPR_LT:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value < right_result->literal_value;
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->literal_value = left_result->literal_value < right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value < right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->literal_value = left_result->literal_value < right_result->literal_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<" are not compatible for less than"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            left_result->kind = EXPR_BOOL_LITERAL;
            delete right_result;
            return_expr = left_result;
			break;
        case EXPR_LTE:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value <= right_result->literal_value;
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->literal_value = left_result->literal_value <= right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value <= right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->literal_value = left_result->literal_value <= right_result->literal_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<" are not compatible for less than or equal to"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            left_result->kind = EXPR_BOOL_LITERAL;
            delete right_result;
            return_expr = left_result;
			break;
        case EXPR_GT:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value > right_result->literal_value;
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->literal_value = left_result->literal_value > right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value > right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->literal_value = left_result->literal_value > right_result->literal_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<" are not compatible for greater than"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            left_result->kind = EXPR_BOOL_LITERAL;
            delete right_result;
            return_expr = left_result;
        case EXPR_GTE:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            result = match_type(left_result, right_result);
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value >= right_result->literal_value;
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->literal_value = left_result->literal_value >= right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = left_result->literal_value >= right_result->literal_value;
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->literal_value = left_result->literal_value >= right_result->literal_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<" are not compatible for greater than or equal"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            left_result->kind = EXPR_BOOL_LITERAL;
            delete right_result;
            return_expr = left_result;
			break;
        case EXPR_EXP:
            if(right_result == nullptr || left_result == nullptr) return nullptr;
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->literal_value = (int) std::pow(left_result->literal_value, right_result->literal_value);
            }
            else if(left_result->kind == EXPR_INT_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = std::pow(left_result->literal_value, right_result->literal_fp_value);
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_INT_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = std::pow(left_result->literal_fp_value, right_result->literal_value);
            }
            else if(left_result->kind == EXPR_FP_LITERAL && right_result->kind == EXPR_FP_LITERAL){
                left_result->kind = EXPR_FP_LITERAL;
                left_result->literal_fp_value = std::pow(left_result->literal_fp_value, right_result->literal_fp_value);
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": types "<<print_kind(left_result->kind)<<" and "<<print_kind(right_result->kind)<<"are not compatible for exponent operations"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            delete right_result;
            return_expr = left_result;
            break;
        case EXPR_NOT:
            if(right_result == nullptr) return nullptr;
            if(right_result->kind == EXPR_BOOL_LITERAL){
                right_result->literal_value = !right_result->literal_value;
            }
            else {
                std::cerr<<"dbl: Line "<<line_num<<": type "<<print_kind(right_result->kind)<<" is not a boolean"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            return_expr = right_result;
			break;
        case EXPR_NEG:
            if(right_result == nullptr) return nullptr;
            if(right_result->kind != EXPR_INT_LITERAL && right_result->kind != EXPR_FP_LITERAL) {
                std::cerr<<"dbl: Line "<<line_num<<": type "<<print_kind(right_result->kind)<<" is not a integer or floating point"<<std::endl;
                error_val = 2;
                return nullptr;
            }
            right_result->literal_value = -(right_result->literal_value);
            return_expr = right_result;
			break;
        case EXPR_INC:
			break;
        case EXPR_DEC:
			break;
        case EXPR_ARG:
			break;
        case EXPR_PRINT_LIST:
            if(left_result == nullptr) return nullptr;
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
                    *new_str += std::string(left_result->literal_value ? "true" : "false");
                    break;
                default:
                    std::cerr<<"dbl: Line "<<line_num<<": no string representation for "<<print_kind(left_result->kind)<<std::endl;
                    error_val = 1;
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
        case EXPR_DEREF:
            if(left_result == nullptr || right_result == nullptr) return nullptr;
            if(right_result->kind != EXPR_INT_LITERAL){
                std::cerr<<"dbl: Line "<<line_num<<": dereference index must be an integer not a "<<print_kind(right_result->kind)<<std::endl;
                error_val = 3;
                return nullptr;
            }
            if(left_result->kind != EXPR_STRING_LITERAL && left_result->kind != EXPR_LIST){
                std::cerr<<"dbl: Line "<<line_num<<": dereference must be on an string or list not a "<<print_kind(left_result->kind)<<std::endl;
                error_val = 3;
                return nullptr;
            }
            if(right_result->literal_value >= left_result->size || right_result->literal_value < 0){
                std::cerr<<"dbl: Line "<<line_num<<": index "<<right_result->literal_value<<" out of range, list is of size "<<left_result->size<<std::endl;
                error_val = 4;
                return nullptr;
            }
            if(left_result->kind == EXPR_LIST){
                list_item *item = left_result->list.at(left_result->size - 1 - right_result->literal_value);
                return_expr = new Expr(item->e->evaluate(table));
            }
            else{
                std::string r = std::string(1, left_result->string_literal.at(right_result->literal_value));
                return_expr = new Expr(EXPR_STRING_LITERAL, r, line_num);
            }
            break;
        case EXPR_PART_EVAL:
            if(right_result == nullptr) return nullptr;
            return_expr = right_result;
            break;
        case EXPR_PROP:
            if(left_result == nullptr) return nullptr;
            if("size" == string_literal){
                if(left_result->kind != EXPR_STRING_LITERAL || left_result->kind != EXPR_LIST)
                return_expr = new Expr(EXPR_INT_LITERAL, left_result->size, line_num);
            }
            else {
                std::cerr<<"dbl: Line: "<<line_num<<": invalid property "<<string_literal<<" provided"<<std::endl;
                error_val = 1;
                return nullptr;
            }
            break;
        case EXPR_LIST:
            return_expr = this;
            break;
        case EXPR_LIST_ITEM:
            {
                if(left_result == nullptr) return nullptr;
                list_item *item = new list_item;
                switch(left_result->kind){
                    case EXPR_INT_LITERAL:
                        item->e = new Expr(EXPR_INT_LITERAL, left_result->literal_value, line_num);
                        item->t = INT;
                        break;
                    case EXPR_STRING_LITERAL:
                        item->e = new Expr(EXPR_STRING_LITERAL, left_result->string_literal, line_num);
                        item->t = STR;
                        break;
                    case EXPR_BOOL_LITERAL:
                        item->e = new Expr(EXPR_BOOL_LITERAL, left_result->literal_value, line_num);
                        item->t = BOOL;
                        break;
                    default:
                        item->e = new Expr(left_result);
                        item->t = OTHER;
                        break;
                }
                if(right_result == nullptr){
                    return_expr = new Expr(EXPR_LIST, nullptr, nullptr, line_num);
                    return_expr->size = 0;
                }
                else {
                    return_expr = right_result;
                }
                return_expr->list.push_back(item);
                return_expr->size++;
            }
            break;
        case EXPR_CALL:
			break;
        case EXPR_INT_LITERAL:
            return_expr = new Expr(this);
			break;
        case EXPR_FP_LITERAL:
            return_expr = new Expr(this);
			break;
        case EXPR_BOOL_LITERAL:
            return_expr = new Expr(this);
			break;
        case EXPR_STRING_LITERAL:
            return_expr = new Expr(this);
			break;
        default:
            break;
    }
    return return_expr;
}
