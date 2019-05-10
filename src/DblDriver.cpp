#include "DblDriver.h"
#include "DblScanner.h"
#include "Expr.h"
#include "Symbol.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

extern int error_val;

namespace yy {

dblDriver::dblDriver () : trace_scanning(false), trace_parsing(false) {
}

dblDriver::~dblDriver() { }

bool dblDriver::parse_stream(std::istream& in, const std::string& sname){
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool dblDriver::parse_file(const std::string& f){
    std::ifstream in(f.c_str());
    if(!in.good()) return false;
    return parse_stream(in, f);
}

bool dblDriver::parse_string(const std::string &input, const std::string& sname){
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

bool dblDriver::evaluate(int argc, char **argv){
    SymbolTable * table = new SymbolTable;
    Expr *argv_list = new Expr(EXPR_LIST, nullptr, nullptr, 0);
    for(int i = argc - 1;i > 0;i--){
        list_item *item = new list_item;
        item->e = new Expr(EXPR_STRING_LITERAL, std::string(argv[i]), 0);
        item->t = STR;
        argv_list->list.push_back(item);
        argv_list->size++;
    }
    Expr *argc_int = new Expr(EXPR_INT_LITERAL, argc - 1, 0);
    Symbol *argv_sym = new Symbol(SYMBOL_GLOBAL, false, "argv", argv_list, nullptr, table);
    Symbol *argc_sym = new Symbol(SYMBOL_GLOBAL, false, "argc", argc_int, nullptr, table);
    table->add_to_level("argv", argv_sym);
    table->add_to_level("argc", argc_sym);
    Line *curr = syntax_tree;
    while(curr){
        if(curr->kind != LINE_ELSE && curr->kind != LINE_ELSE_IF){
            curr->evaluate(table);
            if(error_val != 0){
                return false;
            }
        }
        curr = curr->next;
    }
    return true;
}

void dblDriver::print(){
    syntax_tree->print(0);
}


void dblDriver::print_name(){
    if(syntax_tree) syntax_tree->print_name(0);
}

void dblDriver::error(const class location& l, const std::string& m){
    //std::cerr << "Line " << (int) l << ": "<< m << std::endl;
}

void dblDriver::error(const std::string& m){
    std::cerr << m << std::endl;
}

}
