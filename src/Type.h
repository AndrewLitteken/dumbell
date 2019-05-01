#ifndef TYPE_H
#define TYPE_H

#include "ParamList.h"

typedef enum {
	TYPE_INTEGER,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_BOOL
} type_t;

class Type {
	public:
		Type(type_t, Type *, ParamList *);
		~Type();
		type_t kind;
		Type *subtype;
		ParamList *params; 
}; 
#endif
