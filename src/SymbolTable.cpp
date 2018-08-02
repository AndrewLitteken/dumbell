#include "Symbol.h"
#include "SymbolTable.h"
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <iostream>

SymbolTable::SymbolTable(){
    current_level = 0;
    symbol_list = new std::vector<struct level_info *>;
    struct level_info *level = new struct level_info;
    level->mapping = new std::map<std::string, Symbol *>;
    level->undefined = new std::set<std::string>;
    symbol_list->push_back(level);
}

void SymbolTable::add_level(){
    current_level++;    
    struct level_info *level = new struct level_info;
    level->mapping = new std::map<std::string, Symbol *>;
    level->undefined = new std::set<std::string>;
    symbol_list->push_back(level);
}

void SymbolTable::exit_level(){
    current_level--;    
    delete *(symbol_list->end()-1);
    symbol_list->pop_back();
}

void SymbolTable::add_to_level(std::string n, Symbol *s){
    (*((symbol_list->at(symbol_list->size() - 1))->mapping)).insert(std::make_pair(n, s));
    if(s->def_number == -1){
        (symbol_list->at(symbol_list->size() - 1))->undefined->insert(n);
    }
}

Symbol *SymbolTable::search_level(std::string to_find){
    std::map<std::string, Symbol *> tail_map = *(symbol_list->
        at(symbol_list->size()-1))->mapping;
    std::map<std::string, Symbol *>::iterator found = 
        tail_map.find(to_find);
    if(found == tail_map.end()){
        return nullptr;
    }
    return found->second;
}

Symbol *SymbolTable::search_table(std::string to_find){
    for(std::vector<struct level_info *>::iterator curr = 
        symbol_list->end() - 1;curr != symbol_list->begin() - 1;curr--){
        std::map<std::string, Symbol *>::iterator result = (*curr)->
            mapping->find(to_find);
        if(result != (*curr)->mapping->end()){
            return result->second;
        }
    }
    return nullptr;
}
