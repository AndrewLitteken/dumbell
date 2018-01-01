
#ifndef _INC_PARAM_LIST
#define _INC_PARAM_LIST
#include "param_list.h"
#endif


typedef enum {
	TYPE_INTEGER,
	TYPE_FLOAT
} type_t;

class Type {
	public:
		Type(type_t, Type *, param_list *);
		~Type();
	private:
		type_t kind;
		Type *subtype;
		param_list *params; 
}; 

