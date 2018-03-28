#include "Type.h"
#include "Expr.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include <map>
#include <set>
#include <string>

int overall_def_num = 0;

Symbol::Symbol(symbol_t k, bool def, std::string n, Expr *e, Type *t,
    SymbolTable *table){
    def_number = 0;
    struct iter_info *initial_info = (struct iter_info *)
        malloc(sizeof(struct iter_info));
    initial_info->def_or_expr = def;
    initial_info->definition = e;
    initial_info->type = t;
    dependents = new std::vector<std::string>;
    iter_info.push_back(initial_info);
    if(def) {
        initial_info->label = "D"+std::to_string(overall_def_num);
        overall_def_num++;
        std::set<std::string> dependencies(*process_def());
        add_dependents(&dependencies, table);
    }
}

Symbol::Symbol(std::string n, std::string d){
    def_number = -1;
    dependents = new std::vector<std::string>;
    dependents->push_back(d);
}

std::set<std::string> *Symbol::process_def(){
    return (*(iter_info.end() - 1))->definition->get_expression_deps();
}

void Symbol::add_dependents(std::set<std::string> *dependencies,
        SymbolTable *table){
    std::string d = (*(iter_info.end()-1))->label;
    for(std::set<std::string>::iterator depend = dependencies->begin();
        depend != dependencies->end();depend++){
        Symbol *dependency = table->search_table(*depend); 
        if(dependency){
            dependency->dependents->push_back(d);
        }
        else{
            dependency = new Symbol(*depend, d);
            table->add_to_level(*depend, dependency);
        }
    }
}

void Symbol::redefine(symbol_t s, bool def, Expr* e, Type *t, SymbolTable *table){
    def_number++;
    struct iter_info *new_info = (struct iter_info *)
        malloc(sizeof(struct iter_info));
    new_info->def_or_expr = def;
    new_info->definition = e;
    new_info->type = t;
    iter_info.push_back(new_info);
    if(def){
        new_info->label = "D"+std::to_string(overall_def_num);
        overall_def_num++;
        std::set<std::string> dependencies(*process_def());    
        add_dependents(&dependencies, table); 
    }
}
