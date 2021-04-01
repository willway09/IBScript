#include "LanguageStack.hpp"
#include "RuntimeException.hpp"

void LanguageStack::deleteObject() {
	
}


Function* LanguageStack::getFunction(Variable* var) {
	
	if(var->getType() == Types::LANGUAGEELEMENT) {
		return new Function(*this, var);
	} else {
		throw RuntimeException("Language Element Expected");
	}
}


Variable* LanguageStack::evaluateFunction(std::string& functionName, Variable* parameters) {
	
	if(functionName.compare("push") == 0) {
		
		if(parameters == nullptr  || parameters->getType() == Types::COMMALIST) {
			throw RuntimeException("Expected only one parameter");
		}
		
		if(stackType == Types::OTHER) {
			stackType = parameters->getType();
		} else if(stackType != parameters->getType()) {
			throw RuntimeException("Type mismatch in stack");
		}
		
		variableStack.push(new Variable(parameters));
		return new Variable(nullptr, Types::OTHER, -1);
		
	} else if(functionName.compare("pop") == 0) {
		if(parameters != nullptr) {
			throw RuntimeException("Expected no parameters");
		}
		
		return variableStack.pop();
		
	} else if(functionName.compare("isEmpty") == 0) {
		if(parameters != nullptr) {
			throw RuntimeException("Expected no parameters");
		}
		
		return new Variable(((void*)(new bool(variableStack.isEmpty()))), Types::BOOLEAN, -1);
	} else {
		throw RuntimeException(functionName + " is not a member function of stack");
	}
}