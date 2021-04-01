#ifndef _FUNCTION_HPP
#define _FUNCTION_HPP

#include "Variable.hpp"
class Object;


class Function : public Variable {
	private:
	
		Object& object;
		std::string functionName;
	
	public:
		Function(Object& obj, Variable* name) : object(obj), functionName(*((std::string*)(name->getValue()))), Variable(nullptr, Types::FUNCTION, -1) { }
		
		Variable* evaluate(Variable* parameters);
};

#endif //_FUNCTION_HPP