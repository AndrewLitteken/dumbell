#include "Type.h"
#include "ParamList.h"

Type::Type(type_t k, Type *stype, ParamList *param) {
	kind = k;
	subtype = stype;
	params = param;
}

Type::~Type(void) {

}
