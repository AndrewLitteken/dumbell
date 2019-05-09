#ifndef DBL_DRIVER_H
#define DBL_DRIVER_H
#include <string>
#include <vector>
#include "Line.h"

namespace yy {

class dblDriver {
    public:
        dblDriver();
        ~dblDriver();   
     
        std::string streamname;

        bool trace_scanning;
        bool trace_parsing;

        bool parse_stream(std::istream& in,
            const std::string& sname = "stream input");  

        bool parse_string(const std::string& input,
            const std::string &sname = "string stream");

        bool parse_file(const std::string& filename);

        bool evaluate(int, char **);

        void print();
        void print_name();

        void error(const class location& l, const std::string& m);
        void error(const std::string& m);

        int result;
        std::vector<std::string> tokens;
        Line *syntax_tree;
        class Scanner* lexer;

};

}
#endif
