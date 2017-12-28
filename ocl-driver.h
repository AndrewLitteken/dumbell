#ifndef OCL_DRIVER_H
#define OCL_DRIVER_H
#include <string>
#include <vector>

namespace yy {

class oclDriver {
    public:
        oclDriver();
        ~oclDriver();   
     
        std::string streamname;

        bool trace_scanning;
        bool trace_parsing;

        bool parse_stream(std::istream& in,
            const std::string& sname = "stream input");  

        bool parse_string(const std::string& input,
            const std::string &sname = "string stream");

        bool parse_file(const std::string& filename);

        void error(const class location& l, const std::string& m);
        void error(const std::string& m);

        int result;
        std::vector<std::string> tokens;
        class Scanner* lexer;

};

}
#endif
