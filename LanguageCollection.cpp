#include "LanguageCollection.hpp"
#include "RuntimeException.hpp"

void LanguageCollection::deleteObject() {
	delete collectionIt;
}

Function* LanguageCollection::getFunction(Variable* var) {
	if(var->getType() == Types::LANGUAGEELEMENT) {
		return new Function(*this, var);
	} else {
		throw RuntimeException("Language Element Expected");
	}
}

Variable* LanguageCollection::evaluateFunction(std::string& functionName, Variable* parameters) {
	if(functionName.compare("addItem") == 0) {
		if(parameters == nullptr  || parameters->getType() == Types::COMMALIST) {
			throw RuntimeException("Expected only one parameter");
		}


		variableCollection.add(new Variable(parameters));


		if(collectionType == Types::OTHER) {
			collectionType = parameters->getType();
			collectionIt = variableCollection.getIterator();
		} else if(collectionType != parameters->getType()) {
			throw RuntimeException("Type mismatch in collection");
		} else {
					
		}
		
		return new Variable(nullptr, Types::OTHER, -1);

		
	} else if(functionName.compare("getNext") == 0) {
		if(parameters != nullptr) {
			throw RuntimeException("Expected no parameters");
		}
		
		if(collectionIt == nullptr) collectionIt = variableCollection.getIterator();
		
		Variable* rtn = new Variable(collectionIt->getValue());
		collectionIt->next();
		
		return rtn;
	
	} else if(functionName.compare("resetNext") == 0) {
		if(parameters != nullptr) {
			throw RuntimeException("Expected no parameters");
		}

		delete collectionIt;
		collectionIt = variableCollection.getIterator();
		return new Variable(nullptr, Types::OTHER, -1);
	
	} else if(functionName.compare("hasNext") == 0) {
		
		if(parameters != nullptr) {
			throw RuntimeException("Expected no parameters");
		}
		
		if(collectionIt != nullptr) {
			return new Variable((void*)(new bool(collectionIt->hasMore())), Types::BOOLEAN, -1);
		} else throw RuntimeException("Initialize collection first before accessing");
	} else if(functionName.compare("isEmpty") == 0) {
		if(parameters != nullptr) {
			throw RuntimeException("Expected no parameters");
		}
		
		return new Variable((void*)(new bool(variableCollection.isEmpty())), Types::BOOLEAN, -1);
	} else {
		throw RuntimeException(functionName + " is not a member function of collection");
	}
}