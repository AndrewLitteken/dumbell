#include <iostream>
#include <fstream>

#include "ocl-driver.h"

typedef std::pair<int, bool> scope_info;
std::vector<scope_info> scope_stack;

int main(int argc, char * argv[]){
    yy::oclDriver driver;
    std::fstream infile(argv[1]);
    if(!infile.good()){
        std::cerr <<"Could not open file: "<<argv[1]<<std::endl;
        return 0;
    }
    //driver.trace_scanning = true;
    //driver.trace_parsing = true;
    scope_stack.push_back(std::make_pair(0, false));
    bool result = driver.parse_stream(infile, argv[1]);
    if(result){
        std::cout<<"Parsing successful"<<std::endl;
        return 0;
    }
    else std::cout<<"Parsing unsuccessful"<<std::endl;
    return 1;
}
