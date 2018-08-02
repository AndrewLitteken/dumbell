#ifndef SYMBOL_H
#define SYMBOL_H

#include "Type.h"
#include "Expr.h"
#include "SymbolTable.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class Expr;
class SymbolTable;

typedef enum {
    SYMBOL_GLOBAL,
    SYMBOL_INTERNAL,
    SYMBOL_PARAM
} symbol_t;

struct iter_info {
    bool def_or_expr;
    std::string label;   
    Expr * definition;
    Type * type;
    std::set<std::string> *dependencies;
};

// does each iteration have dependents or does the symbol as a whole have dependents?

// Inclined to say that the symbol as a whole has some set of dependents

// in which case, sbould be moved out of the iter_info struct

// TODO:  Think about this ^

// think about adding scope to the iteration info, maybe with some sort of interger check?

class Symbol {
    public:
        Symbol(symbol_t, bool, std::string, Expr*, Type*, SymbolTable *);
        Symbol(std::string, std::string);
        std::set<std::string> *process_def();
        void add_dependents(std::set<std::string> *, SymbolTable *);
        void redefine(symbol_t, bool, Expr*, Type *, SymbolTable *);
        int def_number;
        int working_set;
        int printed;
        std::string base_name;
        std::vector<struct iter_info *> iter_info;
        std::vector<std::string> *dependents;
};

#endif
