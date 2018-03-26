#ifndef PARAM_LIST_H
#define PARAM_LIST_H

class Type;

#include <string>

class ParamList {
	public:
		ParamList(std::string, Type *, ParamList *);
		~ParamList();
	private:
		std::string name;
		Type *type;
		ParamList *next;
				
};

#endif
