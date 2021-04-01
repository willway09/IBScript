#ifndef _ARRAY_HPP
#define _ARRAY_HPP

#include "Variable.hpp"
class ArrayVariable; //Forward declaration
#include "ArrayVariable.hpp"
#include "Object.hpp"
#include "RuntimeException.hpp"

class Array : public Object {
	private:
		int size;
		
		Types::TypeName arrayType;
		
		Variable** internalArray = nullptr;
		bool initialized = false;
		
	public:
		Array(int sz);
		~Array();
		Types::TypeName getArrayType() { return arrayType; }
		void initializeInternalArray(Types::TypeName t);
		Variable* get(int idx);
		//void set(int idx, Variable* var);
		void deleteObject();
		
		Function* getFunction(Variable* var) { throw RuntimeException("Arrays do not have associated functions"); }
		Variable* evaluateFunction(std::string& functionName, Variable* parameters) { throw RuntimeException("Arrays do not have associated functions"); }
		
		
};

#endif //_ARRAY_HPP