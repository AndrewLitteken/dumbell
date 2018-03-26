#include "type.h"
#include "expr.h"
#include "symbol.h"
#include <map>
#include <set>
#include <string>

Symbol::Symbol(symbol_t k, bool def, std::string n, Expr *e, Type *t){
    def_number = 0;
    struct iter_info *initial_info = (struct iter_info *)
        malloc(sizeof(struct iter_info));
    initial_info->def_or_expr = def;
    initial_info->label = n+std::to_string(def_number);
    initial_info->definition = e;
    initial_info->type = t;
    initial_info->dependents = new std::vector<std::string>;
    iter_info.push_back(initial_info);
    if(def) {
        std::set<std::string> dependencies(*process_def());
    }
}

Symbol::Symbol(std::string n, std::string d){
    def_number = -1;
    base_name = n;
    add_dependents(d);
}

std::set<std::string> *Symbol::process_def(){
    return iter_info[0]->definition->get_expression_deps();
}

void Symbol::add_dependents(std::string d){
    
}
