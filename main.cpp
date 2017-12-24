#include "tokens.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <FlexLexer.h>
using namespace std;

extern token_t yylex();
extern char *yytext;
extern int line_num;

int main(int argc, char * argv[]){
    char *filename;
    filename = argv[1];
    filebuf fb;
    fb.open(filename, std::ios::in);
    istream input(&fb);
    FlexLexer* lexer = new yyFlexLexer(&input);
    while(1) {
        token_t t = (token_t) lexer->yylex();
        if(t == TOKEN_EOF) break;
        else if (t == TOKEN_ERROR){
            cout<<"Line "<<line_num<<": Error"<<endl;
        }
        else {
            cout << token_name(t) << endl;
        }
    }
}
