#ifndef TYPE_H
#define TYPE_H

#include "param_list.h"

typedef enum {
	TYPE_INTEGER,
	TYPE_FLOAT
} type_t;

class Type {
	public:
		Type(type_t, Type *, ParamList *);
		~Type();
	private:
		type_t kind;
		Type *subtype;
		ParamList *params; 
}; 
#endif
