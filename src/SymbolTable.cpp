#include "symbol.h"
#include "SymbolTable.h"
#include <map>
#include <vector>
#include <utility>

SymbolTable::SymbolTable(){
    current_level = 0;
    symbol_list = new std::vector<std::map<std::string, Symbol *> *>;
    std::map<std::string, Symbol * > *new_map = new 
        std::map<std::string, Symbol *>;
    symbol_list->push_back(new_map);
}

void SymbolTable::add_level(){
    current_level++;    
    std::map<std::string, Symbol * > *new_map = new 
        std::map<std::string, Symbol *>;
    symbol_list->push_back(new_map);
}

void SymbolTable::exit_level(){
    current_level--;    
    delete *(symbol_list->end()-1);
    symbol_list->pop_back();
}
