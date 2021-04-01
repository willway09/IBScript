#ifndef _ARRAYVARIABLE_HPP
#define _ARRAYVARIABLE_HPP

#include "Variable.hpp"
class Array; //Forward declaration
#include "Array.hpp"

class ArrayVariable : Variable {
	private:
		Array& parentArray;
	public:
	
		ArrayVariable(void* v, Types::TypeName t, int s, Array& pA) : parentArray(pA), Variable(v, t, s) { }
	
		void setType(Types::TypeName t);
	
	
};

#endif //_ARRAYVARIABLE_HPP