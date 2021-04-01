#include "LanguageQueue.hpp"
#include "RuntimeException.hpp"

void LanguageQueue::deleteObject() {
	
}


Function* LanguageQueue::getFunction(Variable* var) {
	
	if(var->getType() == Types::LANGUAGEELEMENT) {
		return new Function(*this, var);
	} else {
		throw RuntimeException("Language Element Expected");
	}
}


Variable* LanguageQueue::evaluateFunction(std::string& functionName, Variable* parameters) {
	
	if(functionName.compare("enqueue") == 0) {
		
		if(parameters == nullptr  || parameters->getType() == Types::COMMALIST) {
			throw RuntimeException("Expected only one parameter");
		}
		
		if(queueType == Types::OTHER) {
			queueType = parameters->getType();
		} else if(queueType != parameters->getType()) {
			throw RuntimeException("Type mismatch in queue");
		}
		
		variableQueue.enqueue(new Variable(parameters));
		return new Variable(nullptr, Types::OTHER, -1);
		
	} else if(functionName.compare("dequeue") == 0) {
		if(parameters != nullptr) {
			throw RuntimeException("Expected no parameters");
		}
		
		return variableQueue.dequeue();
		
	} else if(functionName.compare("isEmpty") == 0) {
		if(parameters != nullptr) {
			throw RuntimeException("Expected no parameters");
		}
		
		return new Variable(((void*)(new bool(variableQueue.isEmpty()))), Types::BOOLEAN, -1);
	} else {
		throw RuntimeException(functionName + " is not a member function of queue");
	}
}