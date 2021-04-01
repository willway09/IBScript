#ifndef _OBJECT_HPP
#define _OBJECT_HPP

#include "Variable.hpp"
#include <iostream>
class Function;
#include "Function.hpp"

class Object {
	public:
		enum ObjectType {
			ARRAY, STACK, QUEUE, COLLECTION
		};
	
	protected:
		ObjectType type;
		int referenceCount = 0;
		
	public:
		Object(ObjectType t) : type(t), referenceCount(1) { }
		ObjectType getType() { return type; }
		
		void createReference() { referenceCount++; }
		void removeReference() { referenceCount--; if(referenceCount <= 0) deleteObject(); }
		
		virtual void deleteObject() = 0;
		virtual Function* getFunction(Variable* var) = 0;
		virtual Variable* evaluateFunction(std::string& functionName, Variable* parameters) = 0;
};

#endif //_OBJECT_HPP