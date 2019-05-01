#include "Type.h"
#include "Expr.h"
#include "Symbol.h"
#include "SymbolTable.h"
#include <map>
#include <set>
#include <string>
#include <iostream>

int overall_def_num = 0;
int overall_assign_num = 0;

Symbol::Symbol(symbol_t k, bool def, std::string n, Expr *e, Type *t,
    SymbolTable *table){
    defined = true;
    base_name = n;
    def_or_expr = def;
    definition = e;
    type = t;
    dependents = new std::set<std::string>;
    dependencies = process_def();
    func_or_not = false;
    func_body = nullptr;
    if(def) {
        add_to_depedencies(dependencies, table);
    }
    else {
        std::set<std::string> *bad = check_dependencies(dependencies, table);
        if(bad->empty() == false){
            std::cerr<<"ocl: line "<<e->line_num<<": ERROR: definition of "<<
            n<<" uses undefined symbols\n";
            // TODO: add the symbol that are being unsed erete
        }
        delete bad;
    }
}

Symbol::Symbol(std::string n, std::string dependent){
    defined = false;
    base_name = n;
    dependents = new std::set<std::string>;
    dependents->insert(dependent);
    dependencies = new std::set<std::string>;
}

void Symbol::redefine(symbol_t k, bool def, Expr *e, Type *t, 
                      SymbolTable *table){
    func_or_not = false;
    func_body = nullptr;
    defined = true;
    def_or_expr = def;
    definition = e;
    type = t;
    std::set<std::string> *new_dependencies = process_def();
    if(def_or_expr == true){
        for(std::set<std::string>::iterator it = dependencies->begin();
            it != dependencies->end();it++){
            if(new_dependencies->find(*it) == new_dependencies->end()){
                Symbol *dependency_symbol = table->search_table(*it);
                dependency_symbol->dependents->erase(base_name);
            }
        }
        for(std::set<std::string>::iterator it = new_dependencies->begin();
            it != new_dependencies->end();it++){
            if(dependencies->find(*it) == dependencies->end()){
                Symbol *dependency_symbol = table->search_table(*it);
                if(dependency_symbol == nullptr){
                    dependency_symbol = new Symbol(*it, base_name);
                    table->add_to_level(*it, dependency_symbol);
                }
            }
        }
    }
    else{
        std::set<std::string> *bad = check_dependencies(dependencies, table);
        if(bad->empty() == false){
            std::cerr<<"ocl: line "<<e->line_num<<": ERROR: definition of "<<
            base_name<<" uses undefined symbols\n";
            // TODO: add the symbol that are being unsed erete
        }
        delete bad;
    }
    delete dependencies;
    dependencies = new_dependencies;
}

std::set<std::string> *Symbol::process_def(){
    return definition->get_expression_deps();
}

void Symbol::add_to_depedencies(std::set<std::string> *deps, SymbolTable *t){
    for(std::set<std::string>::iterator it = deps->begin();
        it != deps->end();it++){
        Symbol *dependency_symbol = t->search_table(*it);
        if(dependency_symbol == nullptr){
            dependency_symbol = new Symbol(*it, base_name);
            t->add_to_level(*it, dependency_symbol);
        }
        else{
            dependency_symbol->dependents->insert(base_name);
        }
    }
}

std::set<std::string> *Symbol::check_dependencies(std::set<std::string> *deps,
    SymbolTable *t){
    std::set<std::string> *bad_dependencies = new std::set<std::string>;
    for(std::set<std::string>::iterator it = deps->begin();
        it != deps->end();it++){
        Symbol *dependency_symbol = t->search_table(*it);
        if(dependency_symbol == nullptr || dependency_symbol->defined == false){
            bad_dependencies->insert(*it);
        }
    }
    return bad_dependencies;
}
