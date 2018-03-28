#ifndef OCL_SCANNER_H
#define OCL_SCANNER_H

#ifndef YY_DECL

#define YY_DECL                     \
    yy::Parser::token_type             \
    yy::Scanner::lex(              \
    yy::Parser::semantic_type* yylval,     \
    yy::Parser::location_type* yylloc      \
    )
#endif

#include "OclParser.h"

#ifndef __FLEX_LEXER_H
#include "FlexLexer.h"
#endif

namespace yy {

class Scanner: public yyFlexLexer {
    public:
    Scanner(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

    virtual ~Scanner();

    virtual Parser::token_type lex(
        Parser::semantic_type* yylval,
        Parser::location_type* yylloc
    );

    void set_debug(bool b);
};

}

#endif
