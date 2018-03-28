
#include "param_list.h"
#include <string>


ParamList::ParamList(std::string n, Type * t, ParamList * x) {
	name = n;
	type = t;
	next = x; 
}

ParamList::~ParamList(void) {
	
}
