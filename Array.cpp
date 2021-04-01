#include "Array.hpp"

Array::Array(int sz) : Object(ObjectType::ARRAY), size(sz), arrayType(Types::OTHER) {
	
	internalArray = new Variable*[size];
	for(int i = 0; i < size; i++) {
		internalArray[i] = (Variable*)(new ArrayVariable(nullptr, arrayType, -2, *this));
	}
}

Array::~Array() {
	if(internalArray != nullptr)
		deleteObject();
}

void Array::deleteObject() {
	for(int i = 0; i < size; i++) {
		delete internalArray[i];
	}
	delete[] internalArray;
	internalArray = nullptr;
}


Variable* Array::get(int idx) {
	if(idx >= 0 && idx < size) {
		return internalArray[idx];
	} else {
		throw RuntimeException("Attempting to access array out of bounds");
	}
}

//Technically useless
/*void Array::set(int idx, Variable* var) {
	std::cout << "At least set got called" << std::endl;
	if(idx >= 0 && idx < size) {
		if(!initialized) {
			arrayType = var->getType();
			initializeInternalArray();
		}
		
		if(var->getType() == arrayType) {
			internalArray[idx]->setValue(var);
		} else {
			throw RuntimeException("Array-variable type mismatch");
		}
	
	} else {
		throw RuntimeException("Attempting to access array out of bounds");
	}
}*/

void Array::initializeInternalArray(Types::TypeName t) {
	
	arrayType = t;
		
	for(int i = 0; i < size; i++) {
		
		if(internalArray[i]->getType() != Types::OTHER) continue;
		
		switch(arrayType) {
			case Types::INT:
				internalArray[i]->setValue((void*)(new int(0)));
				break;
			case Types::DOUBLE:
				internalArray[i]->setValue((void*)(new double(0.0d)));
				break;
			case Types::BOOLEAN:
				internalArray[i]->setValue((void*)(new bool(false)));
				break;
			case Types::STRING:
				internalArray[i]->setValue((void*)(new std::string("")));
				break;
		}
	}
}
		