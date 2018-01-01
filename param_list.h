
#ifndef _INC_TYPE
#define _INC_TYPE
#include "type.h"
#endif 

#include <string>

class ParamList {
	public:
		ParamList(std::string, Type *, ParamList *);
		~ParamList();
	private:
		std::string name;
		Type *type;
		ParamList *next;
				
}
