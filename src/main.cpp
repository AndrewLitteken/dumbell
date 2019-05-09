#include <iostream>
#include <fstream>

#include "DblDriver.h"

typedef std::pair<int, std::vector<bool> > scope_info;
std::vector<scope_info> scope_stack;
std::vector<Line *> tails;
int error_val = 0;

int main(int argc, char * argv[]){
    yy::dblDriver driver;
    std::fstream infile(argv[1]);
    if(!infile.good()){
        std::cerr <<"Could not open file: "<<argv[1]<<std::endl;
        return 0;
    }
    //driver.trace_scanning = true;
    //driver.trace_parsing = true;
    std::vector<bool> flags;
    flags.push_back(false);
    flags.push_back(false);
    tails.push_back(nullptr);
    scope_stack.push_back(std::make_pair(0, flags));
    bool result = driver.parse_stream(infile, argv[1]);
    if(result){
        driver.evaluate(argc, argv);
    }
    else std::cout<<"Parsing unsuccessful"<<std::endl;
    return 1;
}
