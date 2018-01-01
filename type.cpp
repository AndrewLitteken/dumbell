#include "type.h"


Type::Type(type_t k, Type *stype, param_list *param) {
	kind = k;
	subtype = stype;
	param_list = param;
}

Type::~Type(void) {

}
