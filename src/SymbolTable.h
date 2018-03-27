#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "Symbol.h"
#include <map>
#include <vector>
#include <utility>

class Symbol;

struct level_info {
    std::map<std::string, Symbol * > *mapping;
    std::set<std::string> *undefined;
};

class SymbolTable {
    public:
        SymbolTable();
        void add_level();
        void exit_level();
        void add_to_level(std::string, Symbol *);
        Symbol* search_level(std::string);
        Symbol* search_table(std::string);
        int current_level;
        std::vector<struct level_info *> *symbol_list;
};

#endif
