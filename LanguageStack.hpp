#ifndef _LANGUAGESTACK_HPP
#define _LANGUAGESTACK_HPP

#include "DataStructures/Stack.hpp"
#include "Object.hpp"

class LanguageStack : public Object {
	private:
		Stack<Variable> variableStack;
		Types::TypeName stackType = Types::OTHER;
		
	public:
		LanguageStack() : Object(Object::STACK) { }
		
		void deleteObject();
		Function* getFunction(Variable* var);
		Variable* evaluateFunction(std::string& functionName, Variable* parameters);
};

#endif //_LANGUAGESTACK_HPP