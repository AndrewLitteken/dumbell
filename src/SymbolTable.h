#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "symbol.h"
#include <map>
#include <vector>
#include <utility>

class SymbolTable {
    public:
        SymbolTable();
        void add_level();
        void exit_level();
        Symbol* search_level();
        Symbol* search_table();
        int current_level;
        std::vector<std::map<std::string, Symbol *> *> *symbol_list;
};

#endif
