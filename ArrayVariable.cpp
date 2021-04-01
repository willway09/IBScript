#include "ArrayVariable.hpp"
#include "RuntimeException.hpp"

void ArrayVariable::setType(Types::TypeName t) {
	if(parentArray.getArrayType() == Types::OTHER) {
		Variable::setType(t);
		parentArray.initializeInternalArray(t);
	} else if(t != parentArray.getArrayType()) {
		throw RuntimeException("Type mismatch in array assignment");
	} else {
		Variable::setType(t);
	}
}