#include "decl.h"

Decl::Decl(std::string s, Type * t, Expr * e, Stmt * m, Decl *d) {
	name = s;
	type = t;
	expr = e;
	stmt = m;
	decl = d; 
}

Decl::~Decl(void) {
	
}
