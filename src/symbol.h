#ifndef SYMBOL_H
#define SYMBOL_H

#include "type.h"
#include "expr.h"
#include <map>
#include <string>
#include <vector>

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
    std::vector<std::string> *dependents;
};

class Symbol {
    public:
        Symbol(symbol_t, bool, std::string, Expr*, Type*);
        Symbol(std::string, std::string);
        std::set<std::string> *process_def();
        void add_dependents(std::string);
        int def_number;
        std::string base_name;
        std::vector<struct iter_info *> iter_info;
};

#endif
