#include "OclDriver.h"
#include "OclScanner.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace yy {

oclDriver::oclDriver () : trace_scanning(false), trace_parsing(false) {
}

oclDriver::~oclDriver() { }

bool oclDriver::parse_stream(std::istream& in, const std::string& sname){
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool oclDriver::parse_file(const std::string& f){
    std::ifstream in(f.c_str());
    if(!in.good()) return false;
    return parse_stream(in, f);
}

bool oclDriver::parse_string(const std::string &input, const std::string& sname){
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

bool oclDriver::track_names(){
    SymbolTable * table = new SymbolTable;
    std::cout<<"test1"<<std::endl;
    if(syntax_tree) syntax_tree->name_resolve(table);
    std::cout<<"test2"<<std::endl;
    return true;
}

void oclDriver::print(){
    syntax_tree->print(0);
}


void oclDriver::print_name(){
    if(syntax_tree) syntax_tree->print_name(0);
}

void oclDriver::error(const class location& l, const std::string& m){
    //std::cerr << "Line " << (int) l << ": "<< m << std::endl;
}

void oclDriver::error(const std::string& m){
    std::cerr << m << std::endl;
}

}
