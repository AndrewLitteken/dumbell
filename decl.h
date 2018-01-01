#ifndef _INC_TYPE
#define _INC_TYPE
#include "type.h"
#endif

#ifndef _INC_EXPR
#define _INC_EXPR
#include "expr.h"
#endif

#ifndef _INC_STMT
#define _INC_STMT
#include "stmt.h"
#endif

#include <string>

class Decl {
	public:
		Decl(std::string, Type *, Expr *, Stmt *, Decl *);
		~Decl();
	private:
		std::string name;
		Type *type;
		Expr *value;
		Stmt *code;
		Decl *next;
}
