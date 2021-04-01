#ifndef _LANGUAGECOLLECTION_HPP
#define _LANGUAGECOLLECTION_HPP

#include "DataStructures/SinglyLinkedList.hpp"
#include "Object.hpp"

class LanguageCollection : public Object {
	private:
		SinglyLinkedList<Variable> variableCollection;
		ListIterator<Variable>* collectionIt = nullptr;
		Types::TypeName collectionType = Types::OTHER;
		
	public:
		LanguageCollection() : Object(Object::COLLECTION) { }
		
		void deleteObject();
		Function* getFunction(Variable* var);
		Variable* evaluateFunction(std::string& functionName, Variable* parameters);
};

#endif //_LANGUAGECOLLECTION_HPP