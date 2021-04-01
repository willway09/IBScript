#include "Variable.hpp"
#include "Object.hpp"

Variable::Variable(void* v, Types::TypeName t, int s) : value(v), type(t), scope(s) {
	
}

Variable::Variable(Variable* var) {
	type = var->type;
	scope = var->scope;
	
	switch(type) {
		case Types::INT:
			value = (void*)(new int(*(int*)(var->getValue())));
			break;
		case Types::DOUBLE:
			value = (void*)(new double(*(double*)(var->getValue())));
			break;
		case Types::BOOLEAN:
			value = (void*)(new bool(*(bool*)(var->getValue())));
			break;
		case Types::STRING:
			value = (void*)(new std::string(*(std::string*)(var->getValue())));
			break;
		case Types::OBJECT:
			value = var->getValue();
			((Object*)value)->createReference();
			break;
		case Types::LANGUAGEELEMENT:
			value = (void*)(new std::string(*(std::string*)(var->getValue())));
			break;
	}
}

Variable::~Variable() {
	deleteValue();
}

void Variable::deleteValue() {
	switch(type) {
		case Types::INT:
			delete ((int*)value);
			break;
		case Types::DOUBLE:
			delete ((double*)value);
			break;
		case Types::BOOLEAN:
			delete ((bool*)value);
			break;
		case Types::STRING:
			delete ((std::string*)value);
			break;
		case Types::LANGUAGEELEMENT:
			delete ((std::string*)value);
			break;
		case Types::OBJECT:
			((Object*)value)->removeReference();
			break;
	}
}

void Variable::printDetails() {
	std::cout << "Type: " << Types::getTypeName(type) << ", Scope: " << scope << ", Value: ";
	print();
}

void Variable::print() {
	switch(type) {
		case Types::INT:
			std::cout << *((int*)value);
			break;
		case Types::DOUBLE:
			std::cout << *((double*)value);
			break;
		case Types::BOOLEAN:
			std::cout << (*((bool*)value) == true ? "true" : "false");
			break;
		case Types::STRING:
			std::cout << *((std::string*)value);
			break;
		case Types::LANGUAGEELEMENT:
			std::cout << *((std::string*)value);
			break;
	}
}

void Variable::setType(Types::TypeName t) {
	type = t;
	if(type == Types::OBJECT) {
		((Object*)(value))->createReference();
	}
}

const std::regex Variable::variableRegex = std::regex("^[A-Z]+$");